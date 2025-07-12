#include "clickslider.h"
#include <QMouseEvent>
#include <QStyle>
#include <QStyleOptionSlider>

ClickSlider::ClickSlider(QWidget *parent)
    : QSlider(parent)
{
}

void ClickSlider::mousePressEvent(QMouseEvent *event) {
    QStyleOptionSlider opt;
    initStyleOption(&opt);

    // Проверка, что клик в области ползунка
    QRect groove = style()->subControlRect(QStyle::CC_Slider, &opt, QStyle::SC_SliderGroove, this);
    if (!groove.contains(event->pos())) {
        QSlider::mousePressEvent(event);
        return;
    }

    int pos, sliderMin, sliderMax;
    if (orientation() == Qt::Horizontal) {
        QRect sr = style()->subControlRect(QStyle::CC_Slider, &opt, QStyle::SC_SliderHandle, this);
        sliderMin = sr.width() / 2;
        sliderMax = width() - sliderMin;
        pos = qBound(sliderMin, event->pos().x(), sliderMax);
    } else {
        QRect sr = style()->subControlRect(QStyle::CC_Slider, &opt, QStyle::SC_SliderHandle, this);
        sliderMin = sr.height() / 2;
        sliderMax = height() - sliderMin;
        pos = qBound(sliderMin, event->pos().y(), sliderMax);
    }

    double ratio = (pos - sliderMin) / double(sliderMax - sliderMin);
    int value = minimum() + qRound(ratio * (maximum() - minimum()));
    int oldValue = this->value();
    setValue(value);
    if (value != oldValue) {
        emit sliderClicked(value);
    }
    event->accept();

    QSlider::mousePressEvent(event);
}
