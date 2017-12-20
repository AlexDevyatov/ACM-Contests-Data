import java.io.*;
import java.util.*;

/*
Author: Misha Stassen
method: Dijkstra until at border and add one for the answer.
*/

class Node implements Comparable<Node>
{
    int x,y,dis;
    
    Node(int a,int b,int c)
    {
        x=a;
        y=b;
        dis=c;
    }
    
    public int compareTo(Node b)
    {
        return dis-b.dis;
    }
}

public class QuickHarbourMisha
{
    static final int inf=123456789;
    
    static final int[] dx=new int[]{-1,1,0,0};
    static final int[] dy=new int[]{0,0,-1,1};

    static int[][] dis=new int[1400][1400];
    static char[][] grid=new char[1400][1400];

    static void solve(Scanner sc) throws IOException
    {
        int h=sc.nextInt();
        int w=sc.nextInt();
        int k=sc.nextInt();
        PriorityQueue<Node> pq=new PriorityQueue<Node>();
        for(int i=0;i<h;i++)
        {
            String s=sc.next();
            for(int j=0;j<w;j++)
            {
                grid[i][j]=s.charAt(j);
                dis[i][j]=grid[i][j]=='#'?0:inf;
                if(grid[i][j]=='S')
                    pq.offer(new Node(i,j,0));
            }
        }

        //Dijkstra
        // There is always a solution according to problem statement
        while(!pq.isEmpty())
        {
            Node z=pq.poll();
            int x=z.x;
            int y=z.y;
            int d=z.dis;
            if(d>dis[x][y])
                continue;
            if(x==0||x==h-1||y==0||y==w-1)
            {
                System.out.println(d+1);
                break;
            }
            for(int i=0;i<4;i++)
            {
                int nx=x+dx[i];
                int ny=y+dy[i];
                //if(nx<0||nx>=h||ny<0||ny>=w)
                //    continue;
                int nd=d+1+(grid[nx][ny]=='@'?k:0);
                if(nd<dis[nx][ny])
                {
                    dis[nx][ny]=nd;
                    pq.offer(new Node(nx,ny,nd));
                }
            }
        }
    }

    public static void main(String[] args) throws IOException
    {
        Scanner sc=new Scanner(System.in);
        int n=sc.nextInt();
        for(int i=0;i<n;i++)
            solve(sc);
    }
}