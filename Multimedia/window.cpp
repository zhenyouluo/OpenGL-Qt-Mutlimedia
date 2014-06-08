#include "window.h"
#include "ui_window.h"
#include "mainwidget.h"

Window::Window(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Window)
{
    ui->setupUi(this);
    // Create model
        model = new QStringListModel(this);

        QStringList List;
        QString objects[]={"Sphere","Surface", "Pyramide", "Cuboid", "Cylinder"};
        for(int i=0; i<5; i++) {
            List << objects[i];
            sceneObjects.append(new SceneObject(objects[i]));
        }
        model->setStringList(List);
        ui->listView->setModel(model);

        // Add additional feature so that
        // we can manually modify the data in listView
        // It may be triggered by hitting any key or double-click etc.
        ui->listView->
                setEditTriggers(QAbstractItemView::AnyKeyPressed |
                                QAbstractItemView::DoubleClicked);

            connect(ui->listView->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
                    this, SLOT(onListViewItemClicked(QItemSelection)));



}


void Window::onListViewItemClicked( const QItemSelection & selection)
{
    sceneObjects.at(selection.indexes().at(0).row())->doSomething(this);
//    if (ui->listMail->item(0) == item) {
//        // This is the first item.
//    }
}
Window::~Window()
{
    delete ui;
}

void Window::on_aboutButton_clicked()
{
    QMessageBox::information(
        this,
        tr("About"),
        tr("Authors: Sergey Bolshov, Dawid Jewko, Łukasz Pawluczuk, Adam Beczyński")
       );
}

void Window::on_addTextureButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Image"), "", tr("Image Files (*.png *.jpg *.bmp)"));
   if (fileName.isEmpty()) {
       return;
   } else {
       ui->widget->addTexture(fileName);
   }
}



void Window::on_addButton_clicked()
{
    // Add button clicked
       // Adding at the end

       // Get the position
       int row = model->rowCount();

       // Enable add one or more rows
       model->insertRow(row);

       // Get the row for Edit mode
       QModelIndex index = model->index(model->rowCount()-1);
       model->setData(index, "New object");
       // Enable item selection and put it edit mode
       ui->listView->edit(index);
}
