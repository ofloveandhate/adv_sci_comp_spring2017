#include <iostream>
#include <vector>
#include <cmath>
#include <sstream>
#include <stdexcept>
#include <iomanip>
#include <fstream>
#include <boost/algorithm/string.hpp>

bool is_power_of_2(int k)
{
	return true;
}




struct RBGTriple
{
	// construct from a 0-1 float
	RBGTriple(float h, float s = 0.4f, float v = 1.0f)
	{
		int binned_color = static_cast<int>(h*6);
		float f = h*6 - binned_color;
		float p = v*(1-s);
		float q = v*(1-f*s);
		float t = v*(1 -(1-f)*s);

		switch (binned_color){
			case 0: 
				r = v;
				g = t;
				b = p;
				break;
			case 1: 
				r = q;
				g = v;
				b = p;
				break;
			case 2: 
				r = p;
				g = v;
				b = t;
				break;
			case 3: 
				r = p;
				g = q;
				b = v;
				break;
			case 4: 
				r = t;
				g = p;
				b = v;
				break;
			case 5: 
				r = v;
				g = p;
				b = q;
				break;

		}
	}


	float r;
	float g;
	float b;

	std::string ToString(float range = 255)
	{
		std::stringstream ss;
		ss << std::setfill ('0') << std::hex << std::setw(2) << static_cast<int>(r*range) << std::setw(2) << static_cast<int>(g*range) << std::setw(2) <<  static_cast<int>(b*range);
		return boost::to_upper_copy<std::string>(ss.str());
		
	}


};

struct TaskStat
{
	std::vector<int> depends_on;
	int computes;
	std::vector<int> uses;
	std::vector<int> produces;
	std::vector<int> num_updated_A;
	int critpathlength;
	int j;
	auto ColorLevel() const
	{
		// return j;
		return num_updated_A[1] + num_updated_A[0];
	}
};



std::string SkinParam(int num_levels, std::string name = "level")
{
	std::stringstream ss;

	ss << "skinparam state {\n";
	ss << "	StartColor black\n";
	ss << "	EndColor black\n";
	ss << "	BackgroundColor #FEFECE\n";

	for (int ii=0; ii<num_levels; ++ii)
	{
		ss << "	BackgroundColor<<" << name << ii << ">> " << (RBGTriple(static_cast<float>(ii) / num_levels).ToString()) << "\n";
	}

	ss << "	BorderColor darkred\n";
	ss << "	FontName Times\n";
	ss << "}\n";

	return ss.str();
}

void fft_like(std::vector<int> & A)
{

	constexpr bool close_bottom = false;
	constexpr bool close_top = false;;

	if (!is_power_of_2(A.size()))
		throw std::runtime_error("size of A must be a power of 2");

	std::stringstream ss; 
	ss << "fft_" << std::setfill ('0') << std::setw(4) << A.size() << ".uml";
	std::ofstream out(ss.str().c_str());


	std::vector<int> most_recently_used(A.size(), -1);
	std::vector<int> num_used_A(A.size(), 0);
	std::vector<int> num_updated_A(A.size(), 0);
	std::vector<TaskStat> stats;


	



	using std::pow;
	using std::log2;
	using std::floor;


	int task_counter = 0;

	auto n = A.size();
	int m = floor(log2(A.size()));
	for (int j = 0; j < m; ++j)
	{
		int k = pow(2,j);
		
		for (int i = 0; i < n; ++i)
		{
			int q = i ^ k;
			stats.emplace_back(TaskStat());

			TaskStat& s = stats.back();


			A[i] += A[q]; // line 7
			
			s.depends_on.push_back(most_recently_used[i]);
			s.depends_on.push_back(most_recently_used[q]);

			s.uses.push_back(i);
			s.uses.push_back(q);

			s.computes = i;

			s.num_updated_A.push_back(num_updated_A[i]);
			s.num_updated_A.push_back(num_updated_A[q]);

			if (most_recently_used[i]>=0)
				stats[most_recently_used[i]].produces.push_back(task_counter);
			if (most_recently_used[q]>=0)
				stats[most_recently_used[q]].produces.push_back(task_counter);

			int m1, m2;

			if (most_recently_used[i]>=0)
				m1 = stats[most_recently_used[i]].critpathlength;
			else
				m1 = -1;
			if (most_recently_used[q]>=0)
				m2 = stats[most_recently_used[q]].critpathlength;
			else
				m2 = -1;

			auto m = std::max( m1, m2);
			s.critpathlength = m + 1;

			s.j = j;

			most_recently_used[i] = task_counter;
			++num_updated_A[i];
			++num_used_A[i];
			++num_used_A[q];
			++task_counter;

		}
	}




	auto max_updated = *(std::max_element(std::begin(num_updated_A),std::end(num_updated_A)));

	out << "@startuml\n";
	auto max_level = (*(std::max_element(stats.begin(), stats.end(),
										 [](TaskStat const& s, TaskStat const& t){return s.ColorLevel() < t.ColorLevel();}
										 ))).ColorLevel();

	// 2x to avoid periodic wrapping
	out << SkinParam(2*max_level-1, "ColorLevel");


	for (int ii=0; ii<stats.size(); ++ii)
	{
		const TaskStat& s = stats[ii];


		for (int jj=0; jj<s.depends_on.size(); ++jj)
		{
			auto x = s.depends_on[jj];
			if (close_top && x<0) 
				out << "[*] --> task" << ii << " : " << s.uses[jj] << " \n";
			else if (x >= 0)
				out << "task" << x << " --> task" << ii << " : " << s.uses[jj] << " \n";
				
			
		}
		
		out << "\n";

		out << "state \"Task " << ii << "\" as task" << ii << " <<ColorLevel" <<  s.ColorLevel() <<">> \n";
		out << "state task" << ii << " : " << " A[" << s.computes << "] = A[" << s.uses[0] << "]+A[" << s.uses[1] << "]\\n   A[" << s.uses[0] << "]:" << s.num_updated_A[1] << "   A[" << s.uses[1] << "]:" << s.num_updated_A[0] <<"\n";

		if (close_bottom && s.produces.empty())
			out << "task" << ii << " --> [*]\n"; 

		out << "\n";
	}

	out << "@enduml\n";


	for (int ii=0; ii<n; ++ii)
	{

		auto z = std::count_if(stats.begin(), stats.end(), 
			[=](TaskStat const& s){return s.critpathlength==ii;});
		if (z==0)
			break;
		std::cout<< "critpathlength " << ii << ": " << z << '\n';
	}


	out << "\n\n" << task_counter << " total tasks\n";
}



int main(int arc, char** argv)
{
	std::vector<int> A;

	std::stringstream ss; ss << argv[1];
	int size;
	ss >> size;


	for (int ii=0; ii<size; ++ii)
		A.push_back(ii);

	std::cout << "A: ";
	for (auto x : A)
		std::cout << x << " ";
	std::cout << '\n';

	fft_like(A);

	std::cout << "A: ";
	for (auto x : A)
		std::cout << x << " ";
	std::cout << '\n';
}

