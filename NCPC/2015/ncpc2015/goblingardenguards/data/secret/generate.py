#!/usr/bin/env python3
import random
import math
import itertools

random.seed(4711)


def generate_random(name, gx_min, gx_max, gy_min, gy_max, g_count, mx_min, mx_max, my_min, my_max, mr_min, mr_max, m_count):
    f = open(name, 'w')
    print(g_count, file=f)
    for i in range(g_count):
        f.write(str(random.randint(gx_min, gx_max))+ " "+ str(random.randint(gy_min, gy_max))+"\n")
    print(m_count, file=f)
    for i in range(m_count):
        f.write(str(random.randint(mx_min, mx_max))+ " "+ str(random.randint(my_min, my_max))+" "+ str(random.randint(mr_min, mr_max))+"\n")
    f.close()


def points_in_circum(f, x, y, r, n):
    for i in range(0, n):
        f.write(str(x+int(round((math.cos(2*math.pi/n*i)*r))))+" "+str(y+int(round(math.sin(2*math.pi/n*i)*r)))+"\n")


def generate_circle(name, gx, gy, gr, g_count, mx_min, mx_max, my_min, my_max,mr_min, mr_max,  m_count):
    f = open(name, 'w')
    print(g_count, file=f)
    points_in_circum(f, gx, gy, gr, g_count)
    print(m_count, file=f)
    for i in range(m_count):
        f.write(str(random.randint(mx_min, mx_max))+ " "+ str(random.randint(my_min, my_max))+ " "+ str(random.randint(mr_min, mr_max))+ "\n")
    f.close()


def generate_rectangle(name, n, width, bombsheight, bombswidth, radius, flip=0):
    f = open(name, 'w')
    print(n, file=f)

    bx = width // 2
    goblins = []
    lowest = 0
    for i in range(width):
        d = abs(i - bx)
        available = n // width
        if i < n % width:
            available += 1

        limit = math.floor(math.sqrt(radius ** 2 - d ** 2)) + 1
        for j in range(available // 2):
            goblins.append((i, limit + j))
        for j in range((available + 1) // 2):
            goblins.append((i, -limit - j))
            lowest = min(lowest, -limit - j)

    for i in range(n):
        goblins[i] = (goblins[i][0], goblins[i][1] - lowest)

    random.shuffle(goblins)
    for x in goblins:
        print(x[flip], x[(flip + 1) % 2], file=f)

    print(bombswidth * bombsheight, file=f)
    mx, my = bombswidth // 2, bombsheight // 2
    points = [(x, y) for x in range(bombswidth) for y in range(bombsheight)]
    for p in sorted(points, key=lambda t: math.hypot(t[0] - mx, t[1] - my)):
        r = (p[0] + bx, p[1] - lowest)
        print(r[flip], r[(flip + 1) % 2], radius, file=f)


# generate goblins between two circles, inner_radius and outer_radius
def generate_annulus(name, n, inner_radius, n_sprinklers):
    f = open(name, 'w')
    print(n, file=f)

    outer_radius = math.sqrt(n / math.pi - inner_radius * inner_radius)
    outer_radius = int(math.floor(2 * outer_radius))

    ran = range(-outer_radius, outer_radius+1)
    points = filter(lambda t: t[0] * t[0] + t[1] * t[1] > inner_radius * inner_radius,
                    [(x, y) for x in ran for y in ran])
    goblins = list(itertools.islice(sorted(points, key=lambda t: math.hypot(t[0], t[1])), n))
    random.shuffle(goblins)

    for p in goblins:
        print(p[0] + outer_radius, p[1] + outer_radius, file=f)

    print(n_sprinklers, file=f)
    ran = range(-inner_radius, inner_radius+1)
    points = [(x, y) for x in ran for y in ran]
    for p in itertools.islice(sorted(points, key=lambda t: math.hypot(t[0], t[1])), n_sprinklers):
        print(p[0] + outer_radius, p[1] + outer_radius, inner_radius, file=f)


def generate_unreachable_rectangle(name, n, width, bombsheight, bombswidth, radius, flip=0):
    f = open(name, 'w')
    print(n, file=f)

    goblins = []
    for i in range(width):
        available = n // width
        if i < n % width:
            available += 1

        for j in range(available):
            goblins.append((i, j))

    random.shuffle(goblins)
    for x in goblins:
        print(x[flip], x[(flip + 1) % 2], file=f)

    print(bombswidth * bombsheight, file=f)
    points = [(x + 8000, y + 8000) for x in range(bombswidth) for y in range(bombsheight)]
    for p in points:
        print(p[flip], p[(flip + 1) % 2], radius, file=f)

generate_random("01-small.in", 0, 100, 0, 100, 10, 0, 100, 0, 100, 1, 100, 5)
generate_random("02-small.in", 0, 100, 0, 100, 10, 0, 100, 0, 100, 1, 100, 5)
generate_random("03-small.in", 0, 100, 0, 100, 10, 0, 100, 0, 100, 1, 100, 5)
generate_random("04-medium.in", 0, 1000, 0, 1000, 1000, 0, 1000, 0, 1000, 1, 100, 500)
generate_random("05-medium.in", 0, 1000, 0, 1000, 1000, 0, 1000, 0, 1000, 1, 100, 500)
generate_random("06-medium.in", 0, 1000, 0, 1000, 1000, 0, 1000, 0, 1000, 1, 100, 500)
generate_random("07-large.in", 0, 10000, 0, 10000, 100000, 0, 10000, 0, 10000, 1, 100, 1000)
generate_random("08-horizontal_goblins.in", 1000, 1100, 0, 10000, 100000, 1000, 1100, 0, 10000, 1, 100, 1000)
generate_random("09-vertical_goblins.in", 0, 10000, 1000, 1100, 100000, 0, 10000, 1000, 1100,  1, 100, 1000)
generate_random("10-goblin_cluster_hit.in",  4711, 4811, 4711, 4811, 100000, 4711, 4811, 4711, 4811, 1, 100, 1000)
generate_random("11-goblin_cluster_miss.in", 4711, 4811, 4711, 4811, 100000, 4811, 4811, 4811, 4811, 1, 100, 1000)
generate_circle("12-goblin_circle_inside.in", 1000, 1000, 9, 100000, 1000, 1000, 1000, 1000, 10,10, 1000)
generate_circle("13-goblin_circle_border.in", 1000, 1000, 10, 100000, 1000, 1000, 1000, 1000, 10, 10, 1000)
generate_circle("14-goblin_circle_out.in", 1000, 1000, 11, 100000, 990, 1010, 990, 1010, 10, 10, 1000)
generate_circle("15-goblin_circle_large.in", 1000, 1000, 20, 100000, 990, 1010, 1010, 1010, 10, 10, 1000)
generate_random("16-stripe_horizontal.in", 2000, 2200, 0, 10000, 100000, 2100, 2100, 0, 10000, 100, 100, 1000)
generate_random("17-stripe_vertical.in", 0, 10000, 2000, 2200, 100000, 0, 10000, 2100, 2100, 100, 100, 1000)
generate_random("18-box.in", 4000, 4500, 4000, 4500, 100000, 4200, 4400, 4200, 4400, 100, 100, 1000)
generate_random("19-small-hits.in", 4000, 4500, 4000, 4500, 100000, 4000, 4500, 4000, 4500, 1, 1, 1000)
generate_random("20-smallis-hits.in", 4000, 4500, 4000, 4500, 100000, 4000, 4500, 4000, 4500, 10, 10, 1000)
generate_random("21-small-hits-vertical.in", 4000, 4010, 0, 10000, 100000, 4000, 4010, 5000, 5500, 1, 1, 1000)
generate_random("22-small-hits-horizontal.in", 0, 10000,4000, 4010, 100000, 5000, 5500,4000, 4010, 1, 1, 1000)
generate_rectangle("23-rectangle.in", 100, 21, 11, 11, 10)
generate_rectangle("24-rectangle.in", 10 ** 5, 100, 141, 141, 70)
generate_rectangle("25-rectangle.in", 10 ** 5, 100, 141, 141, 70, flip=1)
generate_unreachable_rectangle("26-unreachable-rectangle.in", 10 ** 5, 100, 141, 141, 70, flip=1)
generate_rectangle("27-rectangle.in", 10 ** 5, 141, 141, 141, 90)
generate_rectangle("28-rectangle.in", 10 ** 5, 141, 141, 141, 90, flip=1)
generate_annulus("29-annullus.in", 10 ** 5, 100, 20000)
