// https://www.acmicpc.net/problem/2628
// 2022-08-17
// `[2022-08-17T15:16, 2022-08-17T16:42]`

#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

#define HOR 0
#define VER 1

using namespace std;

typedef struct {
    int x;
    int y;
} Points;
typedef struct {
    int mode;
    int index;
} SliceInfo;

class Rectangle {
    private:
        Points _rec_points[2];
        int _w;
        int _h;
        int _area;
    public:
        Rectangle (Points i0, Points i1) {
            this->_rec_points[0] = i0;
            this->_rec_points[1] = i1;
            this->_w = abs(_rec_points[0].x - _rec_points[1].x);
            this->_h = abs(_rec_points[0].y - _rec_points[1].y);
            this->_area = this->_w * this->_h;
            return;
        }
        int getArea (void) {
            return this->_area;
        }
        Points * getPoints (void) {
            return this->_rec_points;
        }
};

class SliceTable {
    private:
        Rectangle _R;
        vector<Rectangle> _subR;
        vector<SliceInfo> _slice_info;
        vector<int> hor_index{0};
        vector<int> ver_index{0};
    public:
        SliceTable (Rectangle main_rec) 
        :_R(main_rec){
        }
        void saveSliceInfo(SliceInfo info) {
            this->_slice_info.push_back(info);
            return;
        }
        void slice () {
            for (auto &e: this->_slice_info) {
                if (e.mode == VER) {
                    this->ver_index.push_back(e.index);
                } else {
                    this->hor_index.push_back(e.index);
                }
            }
            this->ver_index.push_back(_R.getPoints()[1].x);
            this->hor_index.push_back(_R.getPoints()[1].y);

            sort(this->ver_index.begin(), this->ver_index.end());
            sort(this->hor_index.begin(), this->hor_index.end());

            for (int v = 1; v < this->ver_index.size(); v++) {
                for (int h = 1; h < this->hor_index.size(); h++) {
                    Rectangle sub_rec(Points {this->ver_index[v - 1], this->hor_index[h - 1]}, Points {this->ver_index[v], this->hor_index[h]});
                    this->_subR.push_back(sub_rec);
                }
            }
            return;
        }
        int findMaxSubRectangleArea (void) {
            vector<int> sub_rec_areas;
            for (auto &r: this->_subR) {
                sub_rec_areas.push_back(r.getArea());
            }
            int max_area = *max_element(sub_rec_areas.begin(), sub_rec_areas.end());
            return max_area;
        }
};

int main (void) {
    int W, H;
    int slice_num;
    cin >> W >> H;
    cin >> slice_num;
    Rectangle R = Rectangle(Points{ 0, 0 }, Points{ W, H });
    SliceTable S = SliceTable (R);
    for (int i = 0; i < slice_num; i++) {
        SliceInfo slice_info;
        cin >> slice_info.mode >> slice_info.index;
        S.saveSliceInfo(slice_info);
    }
    S.slice();
    cout << S.findMaxSubRectangleArea() << endl;
    
    return 0;
}