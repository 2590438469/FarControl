#ifndef USERMANAGE_H
#define USERMANAGE_H

#include <QWidget>

namespace Ui {
class UserManage;
}

class UserManage : public QWidget
{
    Q_OBJECT

public:
    explicit UserManage(QWidget *parent = nullptr);
    ~UserManage();
protected:
    void closeEvent(QCloseEvent *event) override;

public slots:
    void sendAddUserResult(quint8 opResult, quint8 frame, QVector<QVector<QString> > array);

private:
    Ui::UserManage *ui;
signals:
    void disconnectUserManage();
};

#endif // USERMANAGE_H
