#ifndef CHESSBOARDVIEW_H
#define CHESSBOARDVIEW_H

#include <QWidget>

namespace Ui {
class chessBoardView;
}

class chessBoardView : public QWidget
{
    Q_OBJECT

public:
    explicit chessBoardView(QWidget *parent = 0);
    ~chessBoardView();

private slots:
    void on_label_64_linkActivated(const QString &link);

private:
    Ui::chessBoardView *ui;
};

#endif // CHESSBOARDVIEW_H
