/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtWidgets>
#include <QDebug>

#include "echowindow.h"

//! [0]
EchoWindow::EchoWindow()
    : pluginManager(PluginManager::instance())
{
    createGUI();
    setLayout(layout);
    setWindowTitle("Echo Plugin Example");

    if (!loadPlugin()) {
        QMessageBox::information(this, "Error", "Could not load the plugin");
        lineEdit->setEnabled(false);
        button->setEnabled(false);
    }
    else
    {
        qDebug().nospace().noquote() << "Using " << pluginNameLabel->text() << " plugin";
        connect(pluginManager->currentPlugin()->getObject(), SIGNAL(echoSignal(QString)), slotLabel, SLOT(setText(QString)));
    }
}
//! [0]

//! [1]
void EchoWindow::sendEcho()
{
    QString text = pluginManager->currentPlugin()->echo(lineEdit->text());
    label->setText(text);
}
//! [1]

//! [2]
void EchoWindow::createGUI()
{
    pluginNameLabel = new QLabel;
    lineEdit = new QLineEdit;
    label = new QLabel;
    label->setFrameStyle(QFrame::Box | QFrame::Plain);
    slotLabel = new QLabel;
    slotLabel->setFrameStyle(QFrame::Box | QFrame::Plain);
    button = new QPushButton(tr("Send Message"));

    connect(lineEdit, SIGNAL(editingFinished()),
            this, SLOT(sendEcho()));
    connect(button, SIGNAL(clicked()),
            this, SLOT(sendEcho()));

    layout = new QGridLayout;
    layout->addWidget(pluginNameLabel, 0, 0, 1, 2);
    layout->addWidget(new QLabel(tr("Message:")), 1, 0);
    layout->addWidget(lineEdit, 1, 1);
    layout->addWidget(new QLabel(tr("Answer:")), 2, 0);
    layout->addWidget(label, 2, 1);
    layout->addWidget(new QLabel(tr("Signaled Answer:")), 3, 0);
    layout->addWidget(slotLabel, 3, 1);
    layout->addWidget(button, 4, 1, Qt::AlignRight);
    layout->setSizeConstraint(QLayout::SetFixedSize);

    connect(pluginManager, SIGNAL(currentPluginNameChanged(QString)), pluginNameLabel, SLOT(setText(QString)));
}
//! [2]

//! [3]
bool EchoWindow::loadPlugin()
{
    bool loadOk = false;

    foreach (QString pluginName, pluginManager->pluginNames()) {
        bool skipPlugin = pluginManager->currentPlugin() && (qrand() % 2);
        if(skipPlugin)
            continue; // Have some randomness in what plugin is used.
        loadOk = pluginManager->loadPlugin(pluginName);
    }

    return loadOk;
}
//! [3]
