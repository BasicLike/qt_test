// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

//! [0]
#include <QtUiTools>
//! [0]

#include <QApplication>
#include <QLabel>
#include <QSpinBox>
#include <QVBoxLayout>

// 로컬 깃 저장소 커밋, 첫번째 테스트입니다.
// 로컬 깃 저장소 커밋, 2번째 테스트입니다.
// 로컬 깃 저장소 커밋, 3번째 테스트입니다.
// 로컬 깃 저장소 커밋, 4번째 테스트입니다.

#include <QFile>

using namespace Qt::StringLiterals;

//! [1]
static QWidget *loadCalculatorForm(QWidget *parent = nullptr)
{
    QUiLoader loader;

    QFile file(u":/forms/calculatorform.ui"_s);
    if (!file.open(QFile::ReadOnly)) //주석 추가
        return nullptr;
    QWidget *formWidget = loader.load(&file, parent);
    file.close();
    if (formWidget == nullptr)
        return nullptr;
//! [1]

//! [2]
    auto *inputSpinBox1 = formWidget->findChild<QSpinBox*>(u"inputSpinBox1"_s);
    auto *inputSpinBox2 = formWidget->findChild<QSpinBox*>(u"inputSpinBox2"_s);
    auto *outputWidget = formWidget->findChild<QLabel*>(u"outputWidget"_s);
//! [2]

//! [3]
    auto updateResult = [inputSpinBox1, inputSpinBox2, outputWidget]()
    {
        const int sum = inputSpinBox1->value() + inputSpinBox2->value();
        outputWidget->setText(QString::number(sum));
    };
    QObject::connect(inputSpinBox1, &QSpinBox::valueChanged, formWidget, updateResult);
    QObject::connect(inputSpinBox2, &QSpinBox::valueChanged, formWidget, updateResult);
//! [3]

    return formWidget;
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QWidget w;
    auto *formWidget = loadCalculatorForm(&w);
    if (formWidget == nullptr)
        return -1;
    //! [4]
    auto *layout = new QVBoxLayout(&w);
    layout->addWidget(formWidget);
    w.setWindowTitle(QCoreApplication::translate("CalculatorForm",
                                                 "Calculator Builder"));
    //! [4]
    w.show();
    return app.exec();
}
