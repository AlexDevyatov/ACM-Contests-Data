using System;
using System.Collections;
using System.Collections.Generic;

/// <summary>
/// Priority Queue data structure
/// </summary>
public class PriorityQueue<T, C>
	where C : NiceComparer<T>
{
    protected List<T> storedValues;
	protected C comparer;

    public PriorityQueue(C c)
    {
        //Initialize the array that will hold the values
        storedValues = new List<T>();
		
		this.comparer = c;

        //Fill the first cell in the array with an empty value
        storedValues.Add(default(T));
    }

    /// <summary>
    /// Gets the number of values stored within the Priority Queue
    /// </summary>
    public virtual int Count
    {
        get { return storedValues.Count - 1; }
    }
	
    /// <summary>
    /// Returns whether the Priority Queue is empty
    /// </summary>
	public virtual bool IsEmpty
	{
		get { return this.Count == 0; }
	}

    /// <summary>
    /// Returns the value at the head of the Priority Queue without removing it.
    /// </summary>
    public virtual T Peek()
    {
        if (this.Count == 0)
            return default(T); //Priority Queue empty
        else
            return storedValues[1]; //head of the queue
    }

    /// <summary>
    /// Adds a value to the Priority Queue
    /// </summary>
    public virtual void Enqueue(T value)
    {
        //Add the value to the internal array
        storedValues.Add(value);

        //Bubble up to preserve the heap property,
        //starting at the inserted value
        this.BubbleUp(storedValues.Count - 1);
    }

    /// <summary>
    /// Returns the minimum value inside the Priority Queue
    /// </summary>
    public virtual T Dequeue()
    {
        if (this.Count == 0)
            return default(T); //queue is empty
        else
        {
            //The smallest value in the Priority Queue is the first item in the array
            T minValue = this.storedValues[1];

            //If there's more than one item, replace the first item in the array with the last one
            if (this.storedValues.Count > 2)
            {
                T lastValue = this.storedValues[storedValues.Count - 1];

                //Move last node to the head
                this.storedValues.RemoveAt(storedValues.Count - 1);
                this.storedValues[1] = lastValue;

                //Bubble down
                this.BubbleDown(1);
            }
            else
            {
                //Remove the only value stored in the queue
                storedValues.RemoveAt(1);
            }

            return minValue;
        }
    }

    /// <summary>
    /// Restores the heap-order property between child and parent values going up towards the head
    /// </summary>
    protected virtual void BubbleUp(int startCell)
    {
        int cell = startCell;

        //Bubble up as long as the parent is greater
        while (this.IsParentBigger(cell))
        {
            //Get values of parent and child
            T parentValue = this.storedValues[cell / 2];
            T childValue = this.storedValues[cell];

            //Swap the values
            this.storedValues[cell / 2] = childValue;
            this.storedValues[cell] = parentValue;

            cell /= 2; //go up parents
        }
    }

    /// <summary>
    /// Restores the heap-order property between child and parent values going down towards the bottom
    /// </summary>
    protected virtual void BubbleDown(int startCell)
    {
        int cell = startCell;

        //Bubble down as long as either child is smaller
        while (this.IsLeftChildSmaller(cell) || this.IsRightChildSmaller(cell))
        {
            int child = this.CompareChild(cell);

            if (child == -1) //Left Child
            {
                //Swap values
                T parentValue = storedValues[cell];
                T leftChildValue = storedValues[2 * cell];

                storedValues[cell] = leftChildValue;
                storedValues[2 * cell] = parentValue;

                cell = 2 * cell; //move down to left child
            }
            else if (child == 1) //Right Child
            {
                //Swap values
                T parentValue = storedValues[cell];
                T rightChildValue = storedValues[2 * cell + 1];

                storedValues[cell] = rightChildValue;
                storedValues[2 * cell + 1] = parentValue;

                cell = 2 * cell + 1; //move down to right child
            }
        }
    }

    /// <summary>
    /// Returns if the value of a parent is greater than its child
    /// </summary>
    protected virtual bool IsParentBigger(int childCell)
    {
        if (childCell == 1)
            return false; //top of heap, no parent
        else
			return this.comparer.compare(storedValues[childCell / 2], storedValues[childCell]) > 0;
            //return storedValues[childCell / 2].CompareTo(storedValues[childCell]) > 0;
            //return storedNodes[childCell / 2].Key > storedNodes[childCell].Key;
    }

    /// <summary>
    /// Returns whether the left child cell is smaller than the parent cell.
    /// Returns false if a left child does not exist.
    /// </summary>
    protected virtual bool IsLeftChildSmaller(int parentCell)
    {
        if (2 * parentCell >= storedValues.Count)
            return false; //out of bounds
        else
			return this.comparer.compare(storedValues[2 * parentCell], storedValues[parentCell]) < 0;
            //return storedValues[2 * parentCell].CompareTo(storedValues[parentCell]) < 0;
            //return storedNodes[2 * parentCell].Key < storedNodes[parentCell].Key;
    }

    /// <summary>
    /// Returns whether the right child cell is smaller than the parent cell.
    /// Returns false if a right child does not exist.
    /// </summary>
    protected virtual bool IsRightChildSmaller(int parentCell)
    {
        if (2 * parentCell + 1 >= storedValues.Count)
            return false; //out of bounds
        else
			return this.comparer.compare(storedValues[2 * parentCell + 1], storedValues[parentCell]) < 0;
            //return storedValues[2 * parentCell + 1].CompareTo(storedValues[parentCell]) < 0;
            //return storedNodes[2 * parentCell + 1].Key < storedNodes[parentCell].Key;
    }

    /// <summary>
    /// Compares the children cells of a parent cell. -1 indicates the left child is the smaller of the two,
    /// 1 indicates the right child is the smaller of the two, 0 inidicates that neither child is smaller than the parent.
    /// </summary>
    protected virtual int CompareChild(int parentCell)
    {
        bool leftChildSmaller = this.IsLeftChildSmaller(parentCell);
        bool rightChildSmaller = this.IsRightChildSmaller(parentCell);

        if (leftChildSmaller || rightChildSmaller)
        {
            if (leftChildSmaller && rightChildSmaller)
            {
                //Figure out which of the two is smaller
                int leftChild = 2 * parentCell;
                int rightChild = 2 * parentCell + 1;

                T leftValue = this.storedValues[leftChild];
                T rightValue = this.storedValues[rightChild];

                //Compare the values of the children
				if (this.comparer.compare(leftValue, rightValue) <= 0)
                //if (leftValue.CompareTo(rightValue) <= 0)
                    return -1; //left child is smaller
                else
                    return 1; //right child is smaller
            }
            else if (leftChildSmaller)
                return -1; //left child is smaller
            else
                return 1; //right child smaller
        }
        else
            return 0; //both children are bigger or don't exist
    }

}

public class Pirate {
	public int x, L;
	public Pirate(int x, int L) {
		this.x = x; this.L = L;
	}
}

public interface NiceComparer<T> {
	int compare(T o1, T o2);
}

public class compHouse : NiceComparer<Pirate> {
	public int compare(Pirate arg0, Pirate arg1) {
		return (arg0.x - arg1.x);
	}	
}

public class compShip : NiceComparer<Pirate> {
	public int compare(Pirate arg0, Pirate arg1) {
		if (arg0.L == arg1.L) return (arg0.x - arg1.x);
		else return (arg0.L - arg1.L);
	}	
}

public class ParkingShips {
	int N;
	Pirate cap;
	PriorityQueue<Pirate, compHouse> Qx1, Qx2;
	PriorityQueue<Pirate, compShip> QL1, QL2;
	
	public void run() {
		N = int.Parse(System.Console.ReadLine());
		string[] line = System.Console.ReadLine().Split();
		cap = new Pirate(int.Parse(line[0]), int.Parse(line[1]));
		if (cap.L%2 == 1) cap.L++;
		Qx1 = new PriorityQueue<Pirate, compHouse>(new compHouse());
		Qx2 = new PriorityQueue<Pirate, compHouse>(new compHouse());
		QL1 = new PriorityQueue<Pirate, compShip>(new compShip());
		QL2 = new PriorityQueue<Pirate, compShip>(new compShip());
		for (int i = 1; i < N; i++) {
			line = System.Console.ReadLine().Split();
			Pirate P = new Pirate(int.Parse(line[0]), int.Parse(line[1]));
			if (P.x < cap.x) Qx1.Enqueue(P);
			else Qx2.Enqueue(P);
		}
		
		int k = 0;
		int left = int.MinValue;
		while (!Qx1.IsEmpty || !QL1.IsEmpty) {
			if (Qx1.IsEmpty) {
				Pirate P = QL1.Dequeue();
				if (P.x < left) continue;
				if (left + P.L > cap.x - cap.L/2) break;
				left += P.L; k++;
			}
			else if (QL1.IsEmpty) {
				Pirate P = Qx1.Dequeue();
				if (P.x < left) continue;
				if (P.x > cap.x - cap.L/2) break;
				if (P.x - P.L < left) {
					QL1.Enqueue(P); continue;
				}
				left = P.x; k++;
			}
			else {
				Pirate P1 = Qx1.Peek();
				Pirate P2 = QL1.Peek();
				if (P1.x < left + P2.L || (P1.x == left + P2.L && P1.x < P2.x)) {
					Pirate P = Qx1.Dequeue();
					if (P.x < left) continue;
					if (P.x > cap.x - cap.L/2) break;
					if (P.x - P.L < left) {
						QL1.Enqueue(P); continue;
					}
					left = P.x; k++;					
				}
				else {
					Pirate P = QL1.Dequeue();
					if (P.x < left) continue;
					if (left + P.L > cap.x - cap.L/2) break;
					left += P.L; k++;
				}
			}
		}
		
		k++;
		
		left = cap.x + cap.L/2;
		while (!Qx2.IsEmpty || !QL2.IsEmpty) {
			if (Qx2.IsEmpty) {
				Pirate P = QL2.Dequeue();
				if (P.x < left) continue;
				left += P.L; k++;
			}
			else if (QL2.IsEmpty) {
				Pirate P = Qx2.Dequeue();
				if (P.x < left) continue;
				if (P.x - P.L < left) {
					QL2.Enqueue(P); continue;
				}
				left = P.x; k++;
			}
			else {
				Pirate P1 = Qx2.Peek();
				Pirate P2 = QL2.Peek();
				if (P1.x < left + P2.L || (P1.x == left + P2.L && P1.x < P2.x)) {
					Pirate P = Qx2.Dequeue();
					if (P.x < left) continue;
					if (P.x - P.L < left) {
						QL2.Enqueue(P); continue;
					}
					left = P.x; k++;					
				}
				else {
					Pirate P = QL2.Dequeue();
					if (P.x < left) continue;
					left += P.L; k++;
				}
			}
		}
		
		System.Console.WriteLine(k);
	}
	
	public static void Main() {
		int runs = int.Parse(System.Console.ReadLine());
		for (int i = 0; i < runs; i++) new ParkingShips().run();
	}

}
