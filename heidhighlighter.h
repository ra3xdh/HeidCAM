#ifndef HEIDHIGHLIGHTER_H
#define HEIDHIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QObject>

class HeidHighLighter : public QSyntaxHighlighter
{
  Q_OBJECT
public:
    void highlightBlock(const QString &str);
    HeidHighLighter(QTextDocument* parent);
};

#endif // HEIDHIGHLIGHTER_H
