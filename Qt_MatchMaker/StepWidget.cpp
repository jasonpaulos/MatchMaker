#include "DatabaseDialog.h"
#include "StepWidget.h"

StepWidget::StepWidget(DatabaseDialog *parent):
    QWidget(parent),
    dialog(parent)
{
    setGeometry(parent->widgetGeometry);
    setAccessibleName(parent->widgetName);
}

bool StepWidget::canFinish(){
    return true;
}
