#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

template <typename ARG, typename RET = ARG>
class Pipe {
	typedef RET (*transform_t)(ARG);
private:
	transform_t fn;
	const Pipe *next;
public:
	Pipe(transform_t function, Pipe *nextPipe = NULL) : fn(function), next(nextPipe) {}
	void exec(ARG input) const {
		if (next != NULL)
			next->exec(fn(input));
		else
			fn(input);
	}
};

class MergeSort {
public:
	typedef vector<int> iVec;
	typedef vector<iVec> iVec2D;
	static iVec2D mergeFn(const iVec2D &input){
		iVec2D output2D;
		for (iVec2D::const_iterator vec1 = input.begin(), vec2 = vec1 + 1; vec1 < input.end();){
			iVec output1D;
			for (iVec::const_iterator it1 = (*vec1).begin(), it2 = (*vec2).begin(); it1 < (*vec1).end() || it2 < (*vec2).end();)
				if(it2 >= (*vec2).end() || (it1 < (*vec1).end() && *it1 <= *it2))
					output1D.push_back(*it1++);
				else
					output1D.push_back(*it2++);
			output2D.push_back(output1D);
			if (vec1 + 1 < input.end())
				advance(vec1, 2);
			if (vec2 + 1 < input.end())
				advance(vec2, 2);
		}
		printVec(output2D);
		return output2D;
	}
	static void printVec(iVec2D const &in){
		for (iVec2D::const_iterator i = in.begin(); i < in.end(); i++){
			cout << "{ ";
			for (size_t j = 0; j < i->size(); j++)
				cout << setw(2) << i->at(j) << " ";
			cout << "}" << endl;
		}
		cout << endl;
	}
	static void test(){
		int pod_data[8][3] = {
				{1, 9, 17}, {2, 10, 18},
				{5, 13, 21}, {6, 14, 22},
				{3, 11, 19}, {4, 12, 20},
				{7, 15, 23}, {8, 16, 24}
		};
		iVec2D data;
		for (size_t i = 0; i < sizeof(pod_data)/sizeof(pod_data[0]); i++){
			data.push_back(vector<int>());
			for (size_t j = 0; j < sizeof(pod_data[0])/sizeof(pod_data[0][0]); j++)
				data.at(i).push_back(pod_data[i][j]);
		}
		printVec(data);
		typedef Pipe<iVec2D const &, iVec2D> testPipe_t;
		testPipe_t p1(mergeFn), p2(mergeFn, &p1), p3(mergeFn, &p2);
		p3.exec(data);
	}
};

int main() {
	MergeSort::test();
	return 0;
}
