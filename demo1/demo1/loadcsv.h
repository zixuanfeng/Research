//Amended by Josiah
#ifndef _LOAD_CSV_H
#define _LOAD_CSV_H
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>
#include <fstream>
#include <sstream>

class LoadCSV {
private:
	// CSV file name
	std::string fname;

	// Groups of labels with their frequencies: e.g. (Erpos: (Erpos-positive:94,Erpos-negative:67))
	std::vector<std::pair<std::string, std::vector<std::pair<std::string, float>>>> label_freqs;

	int read_file();

public:
	LoadCSV(std::string fname) : fname(fname) { }

	void parseData();

	// Get number of groups
	int getNumGroups();

	// Get group label by index
	std::string getGroupLabel(int n);
	
	typedef  std::vector<std::pair<std::string, float>> lblfreq;
	// Get labels and frequencies of items inside a group
	std::string getInnerGroupLabelFreqs(int n, lblfreq& vs);
};

void LoadCSV::parseData() {
	this->read_file();
}

int LoadCSV::read_file() {
	std::ifstream data(fname, std::ifstream::in);
	if (data.fail()) {
		char buf[500];
		strerror_s(buf, errno);
		printf("%s\n", buf);
	}
	std::string line;

	while (std::getline(data, line)) {
		std::stringstream sstr(line);
		std::string grplabel;
		getline(sstr, grplabel, ',');
		std::string label;
		
		// Parse one row (a group of labels)
		std::vector<std::pair<std::string, float>> gp;

		while (getline(sstr, label, ',')) {
			gp.push_back(std::pair<std::string, float>(label, 0.f));
		}

		// Parse next row (corresponding frequencies)
		getline(data, line);
		std::stringstream sstr2(line);
		std::string freq;
		getline(sstr2, freq, ',');
		int i = 0;
		while (getline(sstr2, freq, ',')) {
			std::stringstream sstr3;
			sstr3 << freq;
			float frq;
			sstr3 >> frq;
			gp[i++].second = frq;
			if (i == gp.size()) {
				break;
			}
		}
		if (i != gp.size()) {
			std::printf("Error: Not enough frequency values.\n");
			return 1;
		}
		else {
			this->label_freqs.push_back(std::pair<std::string, std::vector<std::pair<std::string, float>>>(grplabel, gp));
		}
	}	
	data.close();
	return 0;
}

int LoadCSV::getNumGroups() {
	return this->label_freqs.size();
}

std::string LoadCSV::getGroupLabel(int n) {
	return this->label_freqs[n].first;
}

std::string LoadCSV::getInnerGroupLabelFreqs(int n, lblfreq& vs) {
	if (n > this->getNumGroups()) {
		printf("Error: Only %d groups of points\n", this->getNumGroups());
		return "";
	}
	else {
		vs.assign(this->label_freqs[n].second.begin(), this->label_freqs[n].second.end());		
		return this->label_freqs[n].first;
	}
}

#endif