#include "heidhighlighter.h"
#include <QtGui>

HeidHighLighter::HeidHighLighter(QTextDocument* parent):
    QSyntaxHighlighter(parent)
{

}

void HeidHighLighter::highlightBlock(const QString &str)
{  
    for (int i=0; i<str.length(); i++) {

        QChar b=str.at(i);
        if (b==';') {
            setFormat(i,str.length()-i,Qt::darkGreen);
            break;
        } else  if ((b.isNumber())||(b=='.')||(b=='-')||(b=='+')) {
            setFormat(i,1,Qt::red);
        } else if ((b=='X')||(b=='Y')||(b=='Z')) {
            setFormat(i,1,Qt::blue);
        }
    }
}
