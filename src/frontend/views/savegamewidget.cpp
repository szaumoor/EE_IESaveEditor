#include "savegamewidget.h"
#include "ui_savegamewidget.h"

SaveGameWidget::SaveGameWidget(QWidget* parent)
    : QWidget(parent), ui(new Ui::SaveGameWidget)
{
    ui->setupUi(this);

    //connect()
}

SaveGameWidget::~SaveGameWidget()
{
    delete ui;
}

void SaveGameWidget::inject_data( const GamFile& file )
{
    gam.emplace( file );

    if (!gam)
        return;

    // const auto party_member = file.party_members()[0];
    // const auto cre_party_member = file.party_members_cre()[0];
    //
    // ui->textEdit_2->setText( QString::fromStdString(party_member.character_name.to_string()) );
    // ui->textEdit_3->setText( QString::number( cre_party_member.header().current_hit_points) );
}
