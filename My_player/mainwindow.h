#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QListWidgetItem>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QFileDialog>
#include <QStyle>
#include <QStandardItemModel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

enum class RepeatMode {
    RepeatOne,
    RepeatAll,
    Shuffle
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void loadFileFromPath(const QString &path);
    ~MainWindow();

private slots:
    void on_actionOpen_file_triggered();
    void on_btnPlayPause_clicked();
    void on_btnNext_clicked();
    void on_btnPrev_clicked();
    void on_volumeSlider_sliderMoved(int value);
    void on_positionSlider_sliderMoved(int value);
    void positionChanged(qint64 pos);
    void durationChanged(qint64 dur);
    void on_actionOpen_playlist_triggered();
    void on_tableView_activated(const QModelIndex &index);
    void on_btn_Replay_clicked();
    void on_btn_mute_clicked();

private:
    Ui::MainWindow *ui;
    QMediaPlayer *player;
    QAudioOutput *audioOutput;
    int previousVolume = 50;
    QStringList audioFilePaths;
    qint64 Mduar;
    int currentIndex;
    QString formatChronoTime(qint64 msTotal);
    QStandardItemModel *playlistModel;
    void playFile(int index);
    RepeatMode repeatMode = RepeatMode::RepeatOne;
    void updateAlbumCover(const QString &audioFilePath);

};

#endif // MAINWINDOW_H
