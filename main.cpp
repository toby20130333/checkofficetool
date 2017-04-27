#include "checkdialog.h"
#include <QApplication>
#include "bdwordprocess.h"

///
/// \brief main
/// \param argc
/// \param argv
/// \return -1代表不可以进行正常流程 0 可以进行正常流程
///
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BDWordProcess wordPro;
    wordPro.isInstalledExcel();
    if(wordPro.checkWordExist()){
        CheckDialog w;
        if(w.exec() == QDialog::Accepted){
            return 0;
        }else{
            return -1;
        }
    }else{
       return  0;
    }
}
