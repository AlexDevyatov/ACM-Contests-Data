import java.io.*;
import java.util.*;


public class QuickOut {

	/**
	 * @param args
	 */
	public static void main(String[] args) throws IOException{
		Scanner sc = new Scanner(System.in);
		int casenr = 0;
		int cases = sc.nextInt();
		while(cases-- > 0){
			casenr++;
			solve(sc);
		}
		
	}

	private static void solve(Scanner s) throws IOException{				
		int h = s.nextInt();
		int w = s.nextInt();
		int d = s.nextInt();
		s.nextLine();
		
		char[][] maze = new char[w][h];
		int[][] minTime = new int[w][h];
		
		int startX = 0;
		int startY = 0;
		int endX = 0;
		int endY = 0;
		
		// We gaan nu inlezen
		for(int y = 0; y < h; y++){
			// Regel y
			String line = s.nextLine();
			for(int x = 0; x < w; x++){
				// char X
				maze[x][y] = line.charAt(x);
				if(maze[x][y] != '#' && (y == 0 || y == h-1 || x == 0 || x == w-1)){
					// We zitten op de rand en er is geen land, dus opening!
					endX = x;
					endY = y;
				}
				
				if(maze[x][y] == 'S'){
					// Hier ligt het schip!
					startX = x;
					startY = y;
				}
			}
		}
		
		// We hebben het doolhof ingelezen
		// Nu kunnen we er doorheen gaan lopen!
		Queue<int[]> wacht = new LinkedList<int[]>();
		// In queue, int[]: {x, y, time}

		int[] newPos = {startX, startY, 1};
		wacht.add(newPos);
		
		int minEndTime = Integer.MAX_VALUE;
		
		while(!wacht.isEmpty()){
			int[] currPos = wacht.remove();
			int currTime = currPos[2];

			if(maze[currPos[0]][currPos[1]] == '@')
				currTime += d;	// Brug, dus delay optellen!
			
			if(maze[currPos[0]][currPos[1]] != '#' && currTime < minEndTime && (minTime[currPos[0]][currPos[1]] > currTime || minTime[currPos[0]][currPos[1]] == 0)){
				// We gaan alleen wat doen als we een beter pad hebben gevonden
				
				// We markeren ons bezoek
				minTime[currPos[0]][currPos[1]] = currTime;
				
				if(!(currPos[0] == endX && currPos[1] == endY)){
					// Als we niet op het eind zijn zoeken we door!
					if(currPos[0] > 0){
						int[] nextPos = {currPos[0] - 1, currPos[1], currTime+1};
						wacht.add(nextPos);
					}
					if(currPos[0] < w-1){
						int[] nextPos = {currPos[0] + 1, currPos[1], currTime+1};
						wacht.add(nextPos);
					}
					if(currPos[1] > 0){
						int[] nextPos = {currPos[0], currPos[1] - 1, currTime+1};
						wacht.add(nextPos);
					}
					if(currPos[1] < h-1){
						int[] nextPos = {currPos[0], currPos[1] + 1, currTime+1};
						wacht.add(nextPos);
					}
				}
				else{
					// We zijn op het eind, even het kortste pad markeren
					minEndTime = currTime;
				}

			}
		}
		
		// En het antwoord eruit gooien!
		System.out.println(minEndTime);
	}

}
