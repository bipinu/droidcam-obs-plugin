#pragma once

#include <QtCore/QThread>
#include <QtWidgets/QDialog>
#include <QtGui/QIcon>
#include <QtSvg/QSvgWidget>
#include "ui_AddDevice.h"

typedef struct active_device_info ActiveDeviceInfo;

class AddDevice : public QDialog {
    Q_OBJECT

signals:
    // custom signals (events) go here

public slots:
    // Event handlers go here
    void AddListEntry(const char *name, void* data);
    void ReloadFinish();
    void ReloadList();
    void ClearList();

public:
    QSvgWidget loadingSvg;
    QIcon phoneIcon;
    void *dummy_droidcam_source;
    void *dummy_properties;
    bool enable_audio;
    std::unique_ptr<Ui_AddDeviceDC> ui;
    ~AddDevice();
    explicit AddDevice(QWidget *parent);
    void ShowHideDialog(int show);
    void CreateNewSource(QListWidgetItem *item);
};

class ReloadThread : public QThread {
    Q_OBJECT
    void run() override {
        ReloadList();
        emit ReloadFinish();
    }

private:
    void ReloadList();

signals:
    void AddListEntry(const char *name, void* data);
    void ReloadFinish();

public:
    AddDevice *parent;

};
