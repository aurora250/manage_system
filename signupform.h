#ifndef SIGNUPFORM_H
#define SIGNUPFORM_H

#include <QWidget>

namespace Ui{
class Signup;
}

class Signup : public QWidget{
    Q_OBJECT

public:
    explicit Signup(QWidget *parent = nullptr);
    ~Signup();

private slots:
    void signup_bt_clicked();
    void return_bt_clicked();

private:
    Ui::Signup *ui;
};

#endif // SIGNUPFORM_H
