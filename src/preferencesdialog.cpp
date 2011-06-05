#include <QPushButton>
#include <QColorDialog>
#include "preferencesdialog.h"
#include "ui_preferences.h"
#include "preferences.h"

PreferencesDialog::PreferencesDialog(QWidget* parent) :
	QDialog(parent),
	ui(new Ui::Preferences)
{
	ui->setupUi(this);

	//TODO for now don't display the
	//preferences categories.
	ui->listWidget->hide();
	setupColors();
	setupButtons();
}

void PreferencesDialog::setupColors()
{
	Preferences* p = Preferences::getInstance();
	setColor(ui->markedVertexColorFrame,p->getMarkedVertexColor());
	setColor(ui->vertexColorFrame,p->getVertexColor());
	setColor(ui->markedEdgeColorFrame,p->getMarkedEdgeColor());
	setColor(ui->edgeColorFrame,p->getEdgeColor());
	setColor(ui->markedFacetColorFrame,p->getMarkedFacetColor());
	setColor(ui->facetColorFrame,p->getFacetColor());
}

void PreferencesDialog::setColor(QWidget* w,QColor c)
{
	QString style=QString("* { background-color: rgb(%1,%2,%3); }").arg(c.red()).arg(c.green()).arg(c.blue());
	w->setStyleSheet(style);
}

void PreferencesDialog::setupButtons()
{
	signalMapper = new QSignalMapper(this);
	signalMapper->setMapping(ui->markedVertexColorToolButton,ui->markedVertexColorFrame);
	signalMapper->setMapping(ui->vertexColorToolButton,ui->vertexColorFrame);
	signalMapper->setMapping(ui->markedEdgeColorToolButton,ui->markedEdgeColorFrame);
	signalMapper->setMapping(ui->edgeColorToolButton,ui->edgeColorFrame);
	signalMapper->setMapping(ui->markedFacetColorToolButton,ui->markedFacetColorFrame);
	signalMapper->setMapping(ui->facetColorToolButton,ui->facetColorFrame);

	connect(this->ui->markedVertexColorToolButton,SIGNAL(clicked()),signalMapper,SLOT(map()));
	connect(this->ui->vertexColorToolButton,SIGNAL(clicked()),signalMapper,SLOT(map()));
	connect(this->ui->markedEdgeColorToolButton,SIGNAL(clicked()),signalMapper,SLOT(map()));
	connect(this->ui->edgeColorToolButton,SIGNAL(clicked()),signalMapper,SLOT(map()));
	connect(this->ui->markedFacetColorToolButton,SIGNAL(clicked()),signalMapper,SLOT(map()));
	connect(this->ui->facetColorToolButton,SIGNAL(clicked()),signalMapper,SLOT(map()));

	connect(signalMapper,SIGNAL(mapped(QWidget*)),this,SLOT(colorButtonPressed(QWidget*)));
}

void PreferencesDialog::colorButtonPressed(QWidget* frame)
{
	QColor c = QColorDialog::getColor(Qt::white,this);
	setColor(frame,c);

	Preferences* p = Preferences::getInstance();
	if(frame==ui->markedVertexColorFrame)
		p->setMarkedVertexColor(c);
	else if(frame==ui->vertexColorFrame)
		p->setVertexColor(c);
	else if(frame==ui->markedEdgeColorFrame)
		p->setMarkedEdgeColor(c);
	else if(frame==ui->edgeColorFrame)
		p->setEdgeColor(c);
	else if(frame==ui->markedFacetColorFrame)
		p->setMarkedFacetColor(c);
	else if(frame==ui->facetColorFrame)
		p->setFacetColor(c);
}

PreferencesDialog::~PreferencesDialog()
{
	delete ui;
}