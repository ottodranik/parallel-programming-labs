package lab2;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.Serializable;

public class ArrayCloner implements Serializable {

  private int[][] arr;

  public ArrayCloner() {
    super();
  }

  public ArrayCloner(int[][] arr) {
    super();
    this.arr = arr;
  }

  public int[][] getArr() {
    return arr;
  }

  public void setArr(int[][] arr) {
    this.arr = arr;
  }

  public ArrayCloner clone() {
    ArrayCloner duplicate = null;
    try {
      ByteArrayOutputStream baos = new ByteArrayOutputStream();
      ObjectOutputStream oos = new ObjectOutputStream(baos);
      oos.writeObject(this);
      oos.close();

      ByteArrayInputStream bais = new ByteArrayInputStream(baos.toByteArray());
      ObjectInputStream ois = new ObjectInputStream(bais);
      duplicate = (ArrayCloner) ois.readObject();
      ois.close();
    } catch (Exception e) {
      e.printStackTrace();
    }
    return duplicate;
  }
}