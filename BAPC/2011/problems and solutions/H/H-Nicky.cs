using System;
using System.Collections;
using System.Collections.Generic;


/// <summary>
/// Priority Queue data structure
/// </summary>
public class PriorityQueue<T>
    where T : IComparable
{
    protected List<T> storedValues;

    public PriorityQueue()
    {
        //Initialize the array that will hold the values
        storedValues = new List<T>();

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
            return storedValues[childCell / 2].CompareTo(storedValues[childCell]) > 0;
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
            return storedValues[2 * parentCell].CompareTo(storedValues[parentCell]) < 0;
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
            return storedValues[2 * parentCell + 1].CompareTo(storedValues[parentCell]) < 0;
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
                if (leftValue.CompareTo(rightValue) <= 0)
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


class Pirate : IComparable {
	public long[] t = new long[4];
	public long arrive;
	public int side;
	public Pirate(long t1, long t2, long t3, long t4, long arrive, int side) {
		t[0] = t1; t[1] = t2; t[2] = t3; t[3] = t4; this.arrive = arrive; this.side = side;
	}
	public int CompareTo(Object o) {
		Pirate arg0 = (Pirate)o;
		if (arrive < arg0.arrive) return -1;
		else if (arrive > arg0.arrive) return 1;
		else return ((int)arg0.t[3 - 2 * side] - (int)t[3 - 2 * side]);
	}
}

public class WalkThePlank {
	long N, P, T;
	PriorityQueue<Pirate> Q1, Q2;
	
	public void run() {
		string[] line = System.Console.ReadLine().Split();
		N = long.Parse(line[0]); P = long.Parse(line[1]); T = 0;
		Q1 = new PriorityQueue<Pirate>(); Q2 = new PriorityQueue<Pirate>();
		for (int i = 0; i < P; i++) {
			line = System.Console.ReadLine().Split();
			Q1.Enqueue(new Pirate(long.Parse(line[0]), long.Parse(line[1]), long.Parse(line[2]), long.Parse(line[3]), i - P, 0));
		}
		
		while (!Q1.IsEmpty || !Q2.IsEmpty) {
			Pirate P1 = Q1.Peek(), P2 = Q2.Peek();
			if (P2 == null || (P1 != null && P2.arrive > T && P1.arrive < P2.arrive)) {
				Q1.Dequeue(); 
				if (N - Q2.Count > 0) {
					T = System.Math.Max(T, P1.arrive) + P1.t[0];
					P1.arrive = T + P1.t[1]; P1.side = 1;
					Q2.Enqueue(P1);
				}
			}
			else {
				T = System.Math.Max(T, P2.arrive) + P2.t[2];
				Q2.Dequeue(); P2.arrive = T + P2.t[3]; P2.side = 0; 
				Q1.Enqueue(P2);
				N--;
				if (N == 0) {
					System.Console.WriteLine(T);
					return;
				}
			}
		}
	}
	
	public static void Main() {
		int runs = int.Parse(System.Console.ReadLine());
		for (int i = 0; i < runs; i++) new WalkThePlank().run();
	}

}