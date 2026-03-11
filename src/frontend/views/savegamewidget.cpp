#include "savegamewidget.h"
#include "ui_savegamewidget.h"

SaveGameWidget::SaveGameWidget(QWidget* parent)
    : QWidget(parent), ui(new Ui::SaveGameWidget)
{
    ui->setupUi(this);
}

SaveGameWidget::~SaveGameWidget()
{
    delete ui;
}
