package gui;

import java.util.ArrayList;
import java.util.List;
import java.util.Vector;
import javax.swing.table.AbstractTableModel;

/**
 *
 * @author borgee
 */
class MyTableModel extends AbstractTableModel {

    private String[] columnNames = {"Robot", "Pont"};

    private List<Data> data = new ArrayList<Data>();

    @Override
    public int getColumnCount() {
        return columnNames.length;
    }

    @Override
    public int getRowCount() {
        return data.size();
    }

    @Override
    public Object getValueAt(int row, int col) {
        return data.get(row).get(col);
    }

    public String getColumnName(int col) {
        return columnNames[col];
    }

    public Class getColumnClass(int c) {
        return getValueAt(0, c).getClass();
    }

    public boolean isCellEditable(int row, int col) {
        return false;
    }

    public void insertData(Data value) {
        data.add(value);
        fireTableDataChanged();
    }
}

