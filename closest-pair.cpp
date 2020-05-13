#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include<cmath>
using namespace std;


class point {
public:
    int x;
    int y;

    point() { this->x = 0; this->y = 0; }
    point(int x, int y) { this->x = x; this->y = y; }
    int print_x() { return this->x; }
    int print_y() { return this->y; }

};


void quick_sort(point* a, int start, int end);
int partition(point* a, int start, int end);
double closestpair(point* a, int start, int end);
double distance(point p, point q);
double min_point(point p, point q, point n);

int main()
{

    point A[] = { point(10,15),point(5,15),point(20,3),point(6,1),point(9,7),point(15,9),
    point(8,15) ,point(20,14) ,point(17,13) ,point(16,11) ,point(7,12) ,point(10,10),
    point(1,19) ,point(8,8) ,point(30,9) ,point(22,4) };


    quick_sort(A, 0, 15);


    for (point p : A)
    {
       cout << "(" <<p.print_x()<<","<<p.print_y() << ") ";
    }
    cout << endl;

    double p = closestpair(A, 0,15);
    cout << p << endl;

    return 0;
}
double distance(point p, point q)
{
    return sqrt(((p.x - q.x) * (p.x - q.x)) + ((p.y - q.y) * (p.y - q.y)));
}


double min_point(point p, point q, point n)
{
    double a = distance(p, q);
    double b = distance(p, n);
    double c = distance(q, n);

    double min = (a < b && a < c) ? a : (b < a && b < c) ? b : c;
    return min;
}


void quick_sort(point* a, int start, int end)
{
    if (start < end)
    {
        int pivot = partition(a, start, end);
        quick_sort(a, start, pivot - 1);
        quick_sort(a, pivot + 1, end);
    }
}


int partition(point* a, int start, int end)
{
    int low = start;
    int high = end + 1;
    int pivot = a[start].x;

    do {
        do {
            low++;
        } while (low <= end && a[low].x < pivot);
        do {
            high--;
        } while (high >= start && a[high].x > pivot);

        if (low < high)
        {
            point tmp = a[low];
            a[low] = a[high];
            a[high] = tmp;
        }
    } while (low < high);
    point tmp = a[high];
    a[high] = a[start];
    a[start] = tmp;
    return high;
}

double closestpair(point* a, int start, int end)
{
    int size = end - start;
    double left, right, v_distance;
    double center;

    int index_p = start;

    vector<point> tmp;

    if (size == 1)
        return distance(a[start], a[end]);
    else if (size == 2)
        return min_point(a[start], a[start + 1], a[end]);
    else
    {
        if (size % 2 != 0)
        {
            left = closestpair(a, start, (start + end) / 2);
            right = closestpair(a, (start + end) / 2 + 1, end);
            v_distance = min(left, right);

            while (index_p <= end)
            {
                if (a[index_p].x >= a[(start + end) / 2].x - v_distance && a[index_p].x <= a[(start + end) / 2].x + v_distance)
                    tmp.push_back(a[index_p]);

                index_p += 1;
            }

            center = distance(tmp[0], tmp[1]);

            for (int i = 0; i < tmp.size() - 1; i++)
            {
                for (int j = i + 1; j < tmp.size(); j++)
                {
                    double c = distance(tmp[i], tmp[j]);
                    if (center > c&& fabs(tmp[i].y - tmp[j].y) < c)
                    {
                        center = c;
                    }
                }
            }
            double m = (left < right && left < center) ? left :
                (right < left && right < center) ? right : center;

            return m;
        }
        else
        {
            left = closestpair(a, start, (start + end) / 2 + 1);
            right = closestpair(a, (start + end) / 2 + 2, end);
            v_distance = min(left, right);

            while (index_p <= end)
            {
                if (a[index_p].x >= a[(start + end) / 2 + 1].x - v_distance && a[index_p].x <= a[(start + end) / 2 + 1].x + v_distance)
                    tmp.push_back(a[index_p]);
            }

            center = distance(tmp[0], tmp[1]);
            for (int i = 0; i < tmp.size(); i++)
            {
                for (int j = i + 1; j <= tmp.size(); j++)
                {
                    double c = distance(tmp[i], tmp[j]);
                    if (center > c)
                    {
                        center = c;
                    }
                }
            }
            double m = (left < right && left < center) ? left :
                (right < left && right < center) ? right : center;

            return m;
        }
    }
}
