#ifndef CLICKSLIDER_H
#define CLICKSLIDER_H

#include <QSlider>

class ClickSlider : public QSlider
{
    Q_OBJECT
public:
    explicit ClickSlider(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event) override;

signals:
    void sliderClicked(int value);
};

#endif // CLICKSLIDER_H

