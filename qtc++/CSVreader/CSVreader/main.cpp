#include <QtCore/QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <QStringList>

void writeDataToCSV(const QList<QString>& data, const QString& fileName) {
    // Create a QFile object to handle the file
    QFile file(fileName);

    // Open the file in write-only mode
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        // Create a QTextStream to write data to the file
        QTextStream stream(&file);

        // Loop through each string in the list
        for (const QString& value : data) {
            // Write the string to the file
            stream << value << '\n';
        }

        // Close the file
        file.close();
    }
    else {
        // Handle the case where the file couldn't be opened
        qDebug() << "Error opening file for writing:" << file.errorString();
    }
}


int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);

    // Specify the path to your CSV file
    QString filePath = "C:/Users/user/Desktop/sluzba2/Data.csv";

    // Open the CSV file
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Failed to open file:" << file.errorString();
        return -1;
    }

    // Create a QTextStream to read the CSV file
    QTextStream in(&file);



    // Read and process each line in the CSV file
    int lineIndex = 0;
    const int NameOfExpense = 2;
    const int SecondNameOfExpense= 3;
    const int ExpenseAmmount = 7;
    QList<QString> NameOfExpenseList;
    QList<QString> ExpenseAmmountList;

    while (!in.atEnd())
    {
        // Read a line from the file
        QString line = in.readLine();

        // Split the line into fields using a separator (e.g., comma)
        QStringList fields = line.split(',');

        // Process each field as needed
        int fieldIndex = 0;
        for (const QString& field : fields)
        {
            // Output the index and the field

            // Store the data from lines 2 and 3 in separate QList objects
            if (fieldIndex == NameOfExpense)NameOfExpenseList.append(field);
            if (fieldIndex == SecondNameOfExpense && !field.isEmpty())
            {
                NameOfExpenseList.removeLast();
                NameOfExpenseList.append(field);
            }
            if (fieldIndex == ExpenseAmmount) ExpenseAmmountList.append(field);
            //qDebug() << "Line:" << lineIndex << "Field:" << fieldIndex << field;

            // Increment the field index
            ++fieldIndex;
        }

        // Increment the line index
        ++lineIndex;
    }

    for (const auto& item : NameOfExpenseList) {
        qDebug() << item;}
    for (const auto& item : ExpenseAmmountList) {
        qDebug() << item;
        }
        qDebug() << NameOfExpenseList.size() << ExpenseAmmountList.size();

    QString fileName1 = "C:/Users/user/Desktop/sluzba2/output.csv";
    writeDataToCSV(NameOfExpenseList, fileName1);
    QString fileName2 = "C:/Users/user/Desktop/sluzba2/output2.csv";
    writeDataToCSV(ExpenseAmmountList, fileName2);

    // Close the file
    file.close();

    return a.exec();
}
