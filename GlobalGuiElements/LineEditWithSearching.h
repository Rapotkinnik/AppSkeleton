#ifndef LINEEDITWITHSEARCHING_H
#define LINEEDITWITHSEARCHING_H

#include <QLineEdit>
#include <QComboBox>

class LineEditWithSearching: public QLineEdit
{
    Q_OBJECT

public:
    explicit LineEditWithSearching(QWidget *parent = 0);
    virtual ~LineEditWithSearching();
};

#endif // LINEEDITWITHSEARCHING_H
