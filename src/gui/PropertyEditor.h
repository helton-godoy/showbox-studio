#ifndef PROPERTYEDITOR_H
#define PROPERTYEDITOR_H

#include <QTableWidget>
#include <QObject>

class PropertyEditor : public QTableWidget
{
    Q_OBJECT
public:
    explicit PropertyEditor(QWidget *parent = nullptr);

    // Carrega as propriedades do widget alvo na tabela
    void setTargetWidget(QWidget *widget);

private slots:
    // Chamado quando o usuário edita uma célula
    void onCellValueChanged(int row, int col);

private:
    QWidget *m_target = nullptr;
    bool m_isLoading = false; // Flag para evitar loop de sinal durante o carregamento

    void addPropertyRow(const QString &name, const QVariant &value);
};

#endif // PROPERTYEDITOR_H
