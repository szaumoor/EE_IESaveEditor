#include "savegamewidget.h"
#include "ui_savegamewidget.h"

SaveGameWidget::SaveGameWidget(QWidget* parent)
    : QWidget(parent), ui(new Ui::SaveGameWidget)
{
    ui->setupUi(this);
    connect( ui->pmember_back, &QPushButton::clicked, this, []() {
        qDebug() << "pmember_back";
    } );

    connect( ui->pmember_forward, &QPushButton::clicked, this, []() {
        qDebug() << "pmember_forward";
    } );

    ui->pmember_back->setShortcut( QKeySequence( Qt::CTRL | Qt::Key_Left ) );
    ui->pmember_forward->setShortcut( QKeySequence( Qt::CTRL | Qt::Key_Right ) );
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
    setEnabled( true );
    const auto& party_member = gam->party_members()[0];
    const CreFile& cre_party_member = gam->party_members_cre()[0];
    
    const auto [strength,
                strength_bonus,
                intelligence,
                wisdom,
                dexterity,
                constitution,
                charisma
    ] = cre_party_member.header().stats;

    ui->stat_strength->setValue( strength );
    ui->stat_str_extra->setValue( strength_bonus );
    ui->stat_dexterity->setValue( dexterity );
    ui->stat_constitution->setValue( constitution );
    ui->stat_intelligence->setValue( intelligence );
    ui->stat_wisdom->setValue( wisdom );
    ui->stat_charisma->setValue( charisma );

    const auto [ac_natural,
                ac_effective,
                ac_crushing,
                ac_missile,
                ac_piercing,
                ac_slashing
    ] = cre_party_member.header().armor_class;

    ui->ac_base->setValue( ac_natural );
    ui->ac_effective->setValue( ac_effective );
    ui->ac_piercing->setValue( ac_piercing );
    ui->ac_crush->setValue( ac_crushing );
    ui->ac_slashing->setValue( ac_slashing );
    ui->ac_missile->setValue( ac_missile );

    const auto [resist_fire,
                resist_cold,
                resist_electricity,
                resist_acid,
                resist_magic,
                resist_magic_fire,
                resist_magic_cold,
                resist_slashing,
                resist_crushing,
                resist_piercing,
                resist_missile
    ] = cre_party_member.header().resistances;

    ui->resist_acid->setValue(resist_acid);
    ui->resist_cold->setValue(resist_cold);
    ui->resist_electric->setValue(resist_electricity);
    ui->resist_fire->setValue(resist_fire);
    ui->resist_magic->setValue(resist_magic);
    ui->resist_magic_cold->setValue( resist_magic_cold );
    ui->resist_magic_fire->setValue( resist_magic_fire);
    ui->resist_missile->setValue( resist_missile );
    ui->resist_piercing->setValue( resist_piercing );
    ui->resist_slashing->setValue( resist_slashing );
    ui->resist_crush->setValue( resist_crushing );
    ui->resist_missile->setValue( resist_missile  );

    const auto [saving_throw_vs_death,
                saving_throw_vs_wands,
                saving_throw_vs_poly,
                saving_throw_vs_breath,
                saving_throw_vs_spell
    ] = cre_party_member.header().saving_throws;

    ui->save_death->setValue( saving_throw_vs_death);
    ui->save_wand->setValue( saving_throw_vs_wands);
    ui->save_poly->setValue(saving_throw_vs_poly);
    ui->save_breath->setValue(saving_throw_vs_breath);
    ui->save_spell->setValue(saving_throw_vs_spell);

    ui->name_label->setPlainText( QString::fromStdString( party_member.name.to_string() ) );

}
