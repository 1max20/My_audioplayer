#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "clickslider.h"
#include <QFileDialog>
#include <QDir>
#include <QFileInfo>
#include <QRandomGenerator>
#include <QPixmap>
#include <QFileInfo>
#include <chrono>
#include <iomanip>
#include <sstream>


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
    connect(player, &QMediaPlayer::mediaStatusChanged, this, [this](QMediaPlayer::MediaStatus status)
            {
                if (status == QMediaPlayer::EndOfMedia)
                {
                    switch (repeatMode)
                    {
                    case RepeatMode::RepeatOne:
                        playFile(currentIndex);
                        break;

                    case RepeatMode::RepeatAll:
                        currentIndex = (currentIndex + 1) % audioFilePaths.size();
                        playFile(currentIndex);
                        break;

                    case RepeatMode::Shuffle:
                        currentIndex = QRandomGenerator::global()->bounded(audioFilePaths.size());
                        playFile(currentIndex);
                        break;
                    }
                }
            });

    //Sliders
    player->setAudioOutput(audioOutput);
    audioOutput->setVolume(ui->volumeSlider->value());
    connect(player, &QMediaPlayer::positionChanged, this, &MainWindow::positionChanged);
    connect(player, &QMediaPlayer::durationChanged, this, &MainWindow::durationChanged);
    connect(ui->positionSlider, SIGNAL(sliderClicked(int)), this, SLOT(on_positionSlider_sliderMoved(int)));
    connect(ui->volumeSlider, SIGNAL(sliderClicked(int)), this, SLOT(on_volumeSlider_sliderMoved(int)));

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
    QString FileName = QFileDialog::getOpenFileName(this,tr("Select Audio"),"",tr("Audio Files (*.mp3 *.wav)"));
    player->setSource(QUrl::fromLocalFile(FileName));

    QFileInfo File(FileName);

    ui->File_Name->setText(File.fileName());


}

void MainWindow::playFile(int index)
{
    if (index < 0 || index >= audioFilePaths.size())
        return;

    player->setSource(QUrl::fromLocalFile(audioFilePaths[index]));
    player->play();

    QFileInfo file(audioFilePaths[index]);
    ui->File_Name->setText(file.fileName());
    ui->btnPlayPause->setIcon(QIcon(":/icons/pause.png"));
    ui->tableView->selectRow(index);
    updateAlbumCover(audioFilePaths[index]);
}


void MainWindow::on_tableView_activated(const QModelIndex &index)
{
    currentIndex = index.row();
    playFile(currentIndex);

}


//buttons
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
    if (currentIndex < audioFilePaths.size() - 1)
    {
        currentIndex++;
        playFile(currentIndex);
    }

    if (repeatMode == RepeatMode::Shuffle)
    {
        currentIndex = QRandomGenerator::global()->bounded(audioFilePaths.size());
        playFile(currentIndex);
    }
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

//volumeSlider
void MainWindow::on_volumeSlider_sliderMoved(int value)
{
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


// position slider and time
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


//chossen file from win_files
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

void MainWindow::updateAlbumCover(const QString &audioFilePath)
{
    QPixmap cover;
    cover.load(":/icons/Main_icon2.png");

    ui->albumCoverLabel->setPixmap(
        cover.scaled(ui->albumCoverLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation)
        );
}


