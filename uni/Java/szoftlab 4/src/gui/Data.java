/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package gui;

/**
 *
 * @author borgee
 */
public class Data {
    public int point;
    public int name;

    public Data(int point, int name) {
        this.point = point;
        this.name = name;
    }

    Object get(int col) {
        if (col == 0) {
            return name;
        }
        else if (col == 1) {
            return point;
        }
        else{
            return null;
        }
    }
}

