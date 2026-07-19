#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "clickslider.h"
#include <QFileDialog>
#include <QDir>
#include <QFileInfo>
#include <QRandomGenerator>
#include <QPixmap>
#include <QImage>
#include <QMediaMetaData>
#include <QFileInfo>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <QStatusBar>
#include <QMessageBox>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , player(new QMediaPlayer(this))
    , audioOutput(new QAudioOutput(this))
{
    //btn
    ui->setupUi(this);
    setWindowIcon(QIcon(":/icons/Main_icon.ico"));
    ui->btnPlayPause->setCheckable(true);
    ui->btnPlayPause->setIcon(QIcon(":/icons/play.png"));
    ui->btnNext->setIcon(QIcon(":/icons/next.png"));
    ui->btnPrev->setIcon(QIcon(":/icons/previous.png"));
    ui->btn_Replay->setIcon(QIcon(":/icons/repeat-one.png"));
    ui->btn_mute->setIcon(QIcon(":/icons/volume-mute2.png"));

    //playlist
    playlistModel = new QStandardItemModel(this);
    playlistModel->setHorizontalHeaderLabels(QStringList() << "Название аудиофайла");
    ui->tableView->setModel(playlistModel);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    connect(ui->tableView, &QTableView::doubleClicked, this, [this](const QModelIndex &index)
            {
                currentIndex = index.row();
                playFile(currentIndex);
            });

    //Auto_next_track
    connect(player, &QMediaPlayer::mediaStatusChanged,this, [this](QMediaPlayer::MediaStatus status)
            {
                if (status == QMediaPlayer::LoadedMedia ||
                    status == QMediaPlayer::BufferedMedia)
                {
                    playbackErrorCount = 0;
                }

                if (status == QMediaPlayer::EndOfMedia)
                {
                    playNextTrack();
                }
            });

    //Sliders
    player->setAudioOutput(audioOutput);
    ui->volumeSlider->setRange(0, 100);
    ui->volumeSlider->setValue(20);
    audioOutput->setVolume(0.2);
    previousVolume = 20;

    connect(player, &QMediaPlayer::metaDataChanged, this, &MainWindow::updateAlbumCover); // альбом картинка
    connect(player, &QMediaPlayer::positionChanged, this, &MainWindow::positionChanged);
    connect(player, &QMediaPlayer::durationChanged, this, &MainWindow::durationChanged);
    connect(ui->positionSlider, SIGNAL(sliderClicked(int)), this, SLOT(on_positionSlider_sliderMoved(int)));
    connect(ui->volumeSlider, SIGNAL(sliderClicked(int)), this, SLOT(on_volumeSlider_sliderMoved(int)));
    setDefaultAlbumCover();

    connect(player, &QMediaPlayer::errorOccurred, this, &MainWindow::onPlaybackError);// ошибки

}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_playlist_triggered()
{
    QString folderPath = QFileDialog::getExistingDirectory(this, tr("Open Folder"));
    if (folderPath.isEmpty()) return;

    QDir dir(folderPath);
    QStringList files = dir.entryList(QStringList() << "*.mp3" << "*.wav", QDir::Files);

    audioFilePaths.clear();
    playlistModel->clear();
    playlistModel->setHorizontalHeaderLabels(QStringList() << "Название аудиофайла");

    for (const QString &file : std::as_const(files))
    {
        QString fullPath = dir.absoluteFilePath(file);
        audioFilePaths.append(fullPath);

        QList<QStandardItem*> row;
        row << new QStandardItem(file);
        playlistModel->appendRow(row);
    }

    if (!audioFilePaths.isEmpty())
    {
        currentIndex = 0;
        playFile(currentIndex);
    }
}

void MainWindow::on_actionOpen_file_triggered()
{
    const QString fileName = QFileDialog::getOpenFileName(
        this,
        tr("Select Audio"),
        {},
        tr("Audio Files (*.mp3 *.wav)")
        );

    if (fileName.isEmpty()) {
        return;
    }

    playbackErrorCount = 0;

    loadFileFromPath(fileName);

    setDefaultAlbumCover();

    player->setSource(QUrl::fromLocalFile(fileName));
    player->play();

    const QFileInfo fileInfo(fileName);
    ui->File_Name->setText(fileInfo.fileName());
    ui->btnPlayPause->setIcon(QIcon(":/icons/pause.png"));

    playbackSource = PlaybackSource::SingleFile;
    playbackErrorCount = 0;
}

void MainWindow::playFile(int index)
{
    if (index < 0 || index >= audioFilePaths.size())
        return;

    playbackSource = PlaybackSource::Playlist;
    currentIndex = index;

    setDefaultAlbumCover();

    player->setSource(QUrl::fromLocalFile(audioFilePaths[index]));
    player->play();

    QFileInfo file(audioFilePaths[index]);

    ui->File_Name->setText(file.fileName());
    ui->btnPlayPause->setIcon(QIcon(":/icons/pause.png"));
    ui->tableView->selectRow(index);
}


void MainWindow::on_tableView_activated(const QModelIndex &index)
{
    currentIndex = index.row();
    playFile(currentIndex);

}


//Кнопки
void MainWindow::on_btnPlayPause_clicked()
{
    if (player->playbackState() == QMediaPlayer::PlayingState)
    {
        player->pause();
        ui->btnPlayPause->setIcon(QIcon(":/icons/play.png"));
    }
    else
    {
        player->play();
        ui->btnPlayPause->setIcon(QIcon(":/icons/pause.png"));
    }

}

void MainWindow::on_btnNext_clicked()
{
    if (audioFilePaths.isEmpty())
        return;

    playbackErrorCount = 0;

    if (repeatMode == RepeatMode::Shuffle &&audioFilePaths.size() > 1)
    {
        int newIndex = currentIndex;

        while (newIndex == currentIndex)
        {
            newIndex =
                QRandomGenerator::global()->bounded(audioFilePaths.size());
        }

        currentIndex = newIndex;
    }
    else
    {
        currentIndex =
            (currentIndex + 1) % audioFilePaths.size();
    }

    playFile(currentIndex);
}

void MainWindow::on_btnPrev_clicked()
{
    if (currentIndex > 0)
    {
        currentIndex--;
        playFile(currentIndex);
    }

    if (repeatMode == RepeatMode::Shuffle)
    {
        currentIndex = QRandomGenerator::global()->bounded(audioFilePaths.size());
        playFile(currentIndex);
    }
}

void MainWindow::on_btn_Replay_clicked()
{
    switch (repeatMode)
    {

    case RepeatMode::RepeatOne:
        repeatMode = RepeatMode::RepeatAll;
        ui->btn_Replay->setIcon(QIcon(":/icons/repeat.png"));
        break;
    case RepeatMode::RepeatAll:
        repeatMode = RepeatMode::Shuffle;
        ui->btn_Replay->setIcon(QIcon(":/icons/shuffle.png"));
        break;
    case RepeatMode::Shuffle:
        repeatMode = RepeatMode::RepeatOne;
        ui->btn_Replay->setIcon(QIcon(":/icons/repeat-one.png"));
        break;
    }
}

void MainWindow::on_btn_mute_clicked()
{
    bool muted = audioOutput->isMuted();

    if (!muted)
    {
        previousVolume = ui->volumeSlider->value();
        audioOutput->setMuted(true);
        ui->btn_mute->setIcon(QIcon(":/icons/volume-mute2.png"));
    }
    else
    {
        audioOutput->setMuted(false);
        ui->volumeSlider->setValue(previousVolume);
        audioOutput->setVolume(previousVolume / 100.0);
        ui->btn_mute->setIcon(QIcon(":/icons/volume-medium.png"));
    }
}

//слайдер звука
void MainWindow::on_volumeSlider_sliderMoved(int value)
{
    audioOutput->setVolume(static_cast<float>(value) / 100.0f);
    ui->volumeSlider->setToolTip(QString("%1%").arg(value));
    if (value <= 0)
    {
        audioOutput->setMuted(true);
        ui->btn_mute->setIcon(QIcon(":/icons/volume-mute2.png"));
    }
    else
    {
        audioOutput->setMuted(false);
        audioOutput->setVolume(value / 100.0);
        previousVolume = value;
        ui->btn_mute->setIcon(QIcon(":/icons/volume-medium.png"));
    }

}


// слайдер позиции
void MainWindow::on_positionSlider_sliderMoved(int value)
{
    player->setPosition(value);

}

QString MainWindow::formatChronoTime(qint64 msTotal)
{
    using namespace std::chrono;

    auto duration = milliseconds(msTotal);
    auto hrs   = duration_cast<hours>(duration);
    auto mins  = duration_cast<minutes>(duration % hours(1));
    auto secs  = duration_cast<seconds>(duration % minutes(1));

    std::ostringstream stream;

    if (Mduar >= 3600000) {
        stream << std::setfill('0') << std::setw(2) << hrs.count() << ":"
               << std::setw(2) << mins.count() << ":"
               << std::setw(2) << secs.count();
    } else {
        int totalMins = duration_cast<minutes>(duration).count();
        stream << std::setfill('0') << std::setw(2) << totalMins << ":"
               << std::setw(2) << secs.count();
    }

    return QString::fromStdString(stream.str());
}

//left lebel
void MainWindow::positionChanged(qint64 pos)
{
    if (!ui->positionSlider->isSliderDown())
        ui->positionSlider->setValue(static_cast<int>(pos));

    ui->currentTimeLabel->setText(formatChronoTime(pos));
}

//right lebel
void MainWindow::durationChanged(qint64 dur)
{
    Mduar = dur;
    ui->positionSlider->setMaximum(static_cast<int>(dur));

    ui->timeLabel->setText(formatChronoTime(dur));
}


//выбор файла
void MainWindow::loadFileFromPath(const QString &path)
{
    QFileInfo fileInfo(path);
    QString folderPath = fileInfo.absolutePath();

    QDir dir(folderPath);
    QStringList files = dir.entryList(QStringList() << "*.mp3" << "*.wav", QDir::Files);

    audioFilePaths.clear();
    playlistModel->clear();
    playlistModel->setHorizontalHeaderLabels(QStringList() << "Название аудиофайла");

    int targetIndex = -1;

    for (int i = 0; i < files.size(); ++i) {
        QString fullPath = dir.absoluteFilePath(files[i]);
        audioFilePaths.append(fullPath);

        QList<QStandardItem*> row;
        row << new QStandardItem(files[i]);
        playlistModel->appendRow(row);

        if (QFileInfo(fullPath).canonicalFilePath() == QFileInfo(path).canonicalFilePath())
            targetIndex = i;
    }

    if (targetIndex != -1) {
        currentIndex = targetIndex;
        playFile(currentIndex);
    }
}

// картинка альбома
void MainWindow::updateAlbumCover()
{
    const QMediaMetaData metadata = player->metaData();
    QImage cover = metadata.value(QMediaMetaData::CoverArtImage).value<QImage>();

    if (cover.isNull()) {
        cover = metadata.value(QMediaMetaData::ThumbnailImage).value<QImage>();
    }
    if (cover.isNull()) {
        setDefaultAlbumCover();
        return;
    }

    ui->albumCoverLabel->setPixmap(
        QPixmap::fromImage(cover).scaled(ui->albumCoverLabel->size(), Qt::KeepAspectRatio,Qt::SmoothTransformation));
}

void MainWindow::setDefaultAlbumCover()
{
    const QPixmap defaultCover(":/icons/Main_icon2.png");

    ui->albumCoverLabel->setPixmap(defaultCover.scaled(ui->albumCoverLabel->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
}

// Обработка ошибки

void MainWindow::onPlaybackError(
    QMediaPlayer::Error error,
    const QString &errorString)
{
    if (error == QMediaPlayer::NoError)
        return;
    const QString filePath = player->source().toLocalFile();
    const QString fileName = QFileInfo(filePath).fileName();
    const QString reason = errorString.isEmpty()? tr("Неизвестная ошибка воспроизведения") : errorString;

    player->stop();

    if (playbackSource == PlaybackSource::SingleFile)
    {
        QMessageBox::warning(this, tr("Ошибка воспроизведения"),tr("Не удалось воспроизвести файл:\n%1\n\nПричина:\n%2").arg(fileName.isEmpty() ? filePath : fileName, reason));
        return;
    }

    if (audioFilePaths.isEmpty())
        return;

    ++playbackErrorCount;

    statusBar()->showMessage(
        tr("Не удалось воспроизвести \"%1\". "
           "Переход к следующему треку.")
            .arg(fileName),
        5000);

    if (playbackErrorCount >= audioFilePaths.size())
    {
        playbackErrorCount = 0;
        player->stop();

        QMessageBox::warning(this, tr("Ошибка плейлиста"), tr("Не удалось воспроизвести ни один файл из плейлиста."));
        return;
    }

    skipBrokenTrack();
}
void MainWindow::playNextTrack()
{
    if (audioFilePaths.isEmpty())
        return;

    switch (repeatMode)
    {
    case RepeatMode::RepeatOne:playFile(currentIndex);
        break;

    case RepeatMode::RepeatAll:currentIndex = (currentIndex + 1) % audioFilePaths.size();
        playFile(currentIndex);
        break;

    case RepeatMode::Shuffle:
        if (audioFilePaths.size() == 1)
        {
            currentIndex = 0;
        }
        else
        {
            int newIndex = currentIndex;

            while (newIndex == currentIndex)
            {
                newIndex =QRandomGenerator::global()->bounded(audioFilePaths.size());
            }

            currentIndex = newIndex;
        }

        playFile(currentIndex);
        break;
    }
}

void MainWindow::skipBrokenTrack()
{
    if (audioFilePaths.isEmpty())
        return;

    currentIndex = (currentIndex + 1) % audioFilePaths.size();
    playFile(currentIndex);
}
