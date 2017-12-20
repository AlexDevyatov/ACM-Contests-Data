import sys, math

def getTriangleArea(p1, p2, p3):
    dx1=p2[0]-p1[0]
    dy1=p2[1]-p1[1]
    dx2=p3[0]-p1[0]
    dy2=p3[1]-p1[1]
    return abs(dx1*dy2-dx2*dy1)	
	
def getConvexArea(points):
    res = 0
    for i in range(2, len(points)):
        res += getTriangleArea(points[0], points[i-1], points[i])
    return res;
	
def getMiddle(points, a, b):
    return [(points[a][0]+points[b][0])/2,(points[a][1]+points[b][1])/2]
	
def getCuttedArea(points):
    res=0
    n=len(points)
    for i in range(n):
        left = (i+1)%n
        right = (i+n-1)%n
        p2 = getMiddle(points, i, left)
        p3 = getMiddle(points, i, right)
        res += getTriangleArea(points[i], p2, p3)
    return res;

def run():
    an = sys.stdin.readline().split()
    a = float(an[0])
    N = int(an[1])
    
    points = []
    for i in range(N):
        coords = sys.stdin.readline().split()
        points.append([int(coords[0])*2, int(coords[1])*2])
        # //x2, thus middle point of the edges are integer
    
    wholeArea = getConvexArea(points)
    maxCuttedArea = getCuttedArea(points)
    
    maxCuttedAreaRelative = float(maxCuttedArea)/wholeArea
    scaleFactor = math.sqrt((1.0-a)/maxCuttedAreaRelative)
    
    
    print(2.0/scaleFactor)
    
	
run()
