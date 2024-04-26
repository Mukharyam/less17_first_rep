#include <bits/stdc++.h>
#include <windows.h>
//#include <psapi.h>
//#include <utility>
#define ll long long
#define ull unsigned long long
#define ld long double
#define print_lst_1x(lst) for (auto el: lst){cout << el << ' ';} cout << endl;
#define print_lst_2x(lst) for (auto el: lst){for (auto zn: el) {cout << zn << ' ';} cout << '\n';} cout << endl;
using namespace std;


int DFS(int ver, int lengh, vector <bool> was, vector <vector <int>>& graf){
    was[ver] = true;
    int max_lengh = lengh;

    for (int v: graf[ver]){
        if (!was[v]) {
            int lp = DFS(v, lengh + 1, was, graf);
            max_lengh = max(max_lengh, lp);
        }
    }
    return max_lengh;
}


int kuhn_algorithm(int n, vector <int> vertices, vector <vector <int>>& graf){
    int max_par_soch = -1;
    vector <bool> was(n, false);

    for (int ver: vertices){
        max_par_soch = max(max_par_soch, (DFS(ver, 0, was, graf) + 1) / 2);
    }
    return max_par_soch;
}


vector <int> division_into_shares(int n, vector <vector <int>>& graf){
    /**
     Функция разделит граф на доли и вернёт
     вектор доли с наименьшим количеством вершин
     **/
    vector <int> share1, share2;
    bool flag = true;
    int start = 0;

    vector <bool> was (n, false);
    was[start] = true;
    vector <int> step_now = {start};
    vector <int> sosedi;

    while (true){
        for (int ver: step_now){
            if (flag){
                share1.push_back(ver);
            } else {
                share2.push_back(ver);
            }
            for (int sos: graf[ver]){
                if (!was[sos]){
                    sosedi.push_back(sos);
                    was[sos] = true;
                }
            }
        }
        flag = !flag;
        if (sosedi.empty()){
            break;
        }
        step_now = sosedi;
        sosedi.clear();
    }
//    print_lst_1x(share1);
//    print_lst_1x(share2);

    return (share1.size() < share2.size())? share1:share2;
}


int main(){
    int n, m;
    cin >> n >> m;
    vector <vector <int>> graf(n);

    int v1, v2;
    for (int i = 0; i < m; i++){
        cin >> v1 >> v2;
        graf[v1].push_back(v2);
        graf[v2].push_back(v1);
    }

    // запуск без предобработки
    vector <int> vertices;
    for (int i = 0; i < n; i++){
        vertices.push_back(i);
    }
    cout << kuhn_algorithm(n, vertices, graf) << endl;

    // предобработаем граф, предвариьтельно разделив его на доли
    // и запустив алгоритм куна только по одной из долей.
    // очевидно математически, что выгоднее запускать алгоритм Куна
    // на доли с наименьшим количеством вершин, так как таким способом
    // мы сделаем меньше запуска дфс. Ответ же от этого не изменится
    // в силу чередования вершин то из левой, то из правой доли.
    cout << kuhn_algorithm(n, division_into_shares(n, graf), graf) << endl;

}


/**
Примеры входных данных (графы):

8 7
0 4
1 4
1 5
1 6
2 6
3 6
3 7

8 7
0 5
1 4
1 5
1 6
2 6
3 6
3 7

8 7
0 1
0 2
0 3
0 4
0 5
0 6
0 7

 */