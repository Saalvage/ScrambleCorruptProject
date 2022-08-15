#include <iostream>
#include <string>
#include <deque>
#include <filesystem>
#include <random>

namespace fs = std::filesystem;

int main(int argc, const char** argv) {
	std::string dir;

	if (argc == 2) {
		dir = argv[2];
	} else {
		std::cout << "Give me a file: ";
		std::getline(std::cin, dir);
	}

	if (dir.at(0) == '"' && dir.at(dir.size() - 1) == '"') {
		dir = dir.substr(1, dir.size() - 2);
	}

	std::deque<fs::directory_entry> files;

	for (const fs::directory_entry& file : fs::recursive_directory_iterator(dir)) {
		fs::path ext = file.path().extension();
		if (ext == ".jpg" || ext == ".png") {
			files.push_back(file);
		}
	}

	std::string newDir = dir + "texstsda2";
	fs::copy(dir, newDir, fs::copy_options::recursive);

	std::random_device dev;
	std::default_random_engine gen(dev());
	for (const fs::directory_entry& file : fs::recursive_directory_iterator(newDir)) {
		fs::path ext = file.path().extension();
		if (ext == ".jpg" || ext == ".png") {
			fs::copy_file(files[std::uniform_int_distribution<int>(0, files.size() - 1)(gen)], file, fs::copy_options::overwrite_existing);
		}
	}
}
