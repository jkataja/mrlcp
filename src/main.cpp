#include <iostream>
#include <fstream>
#include <stdexcept>
#include <memory>
#include <cstdio>
#include <sys/types.h>
#include <sys/stat.h>
#include <boost/program_options.hpp>
#include <boost/iostreams/device/mapped_file.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>

#include "context.hpp"
#include "lcplen.hpp"

namespace po = boost::program_options;
namespace fs = boost::filesystem;

#define SELF "mrlcp"
#define USAGE "Usage: " SELF " [-n | -p | -o | -h] [options]... input-key work-dir\n" \
	"Naive longest common prefix array construction.\n" \
	"\n"

int main(int argc, char *argv[]) {

	// Create non-executable files
	mode_t mask = umask(0111);
	umask(mask | (S_IXUSR | S_IXGRP | S_IXOTH));

	uint32 in_key = 0;
	uint32 out_keys = 0;

	std::string filename_text;
	std::string filename_sa;
	std::string filename_lcp;
	std::string workdir;

	try {
		po::options_description visible_opts("Options");
		visible_opts.add_options()
			( "naive,n", "Compute LCP using naive algorithm" )
			( "permuted,p", "Compute Permuted LCP using Irreducible LCP algorithm" )
			( "order,o", "Re-order Permuted LCP to LCP in suffix array order" )
			( "help,h", "Show this help and exit" )
			( "keys,k", po::value<uint32>(&out_keys)->default_value(255), 
			  "Maximum number of output keys" 
			)
			( "text,t", po::value<std::string>(&filename_text), "Input text")
			( "sa,s", po::value<std::string>(&filename_sa), "Suffix array")
			( "plcp,P", po::value<std::string>(&filename_lcp), "PLCP array")
			;

		po::options_description hidden_opts;
		hidden_opts.add_options()
			( "key", po::value<uint32>(&in_key), "Input key to process" )
			( "work-dir", po::value<std::string>(&workdir), 
			  "working directory where intermediate files are placed"
			)
			;
		
		po::positional_options_description p;
		p.add("key", 1);
		p.add("work-dir", 1);

		po::options_description opts;
		opts.add(visible_opts).add(hidden_opts);

		po::variables_map vm;
		po::store(po::command_line_parser(argc, argv).
				options(opts).positional(p).run(), vm);
		po::notify(vm);

		// Jobs range
		if (in_key > 255 || out_keys > 255) {
			std::cerr << SELF << ": key not in accepted range [0,255]" 
				<< std::endl << std::flush;
			return EXIT_FAILURE;
		}

		// No input
		if (!vm.count("work-dir")) {
			std::cerr << SELF << ": working directory not specified" 
				<< std::endl << std::flush;
		}

		// Help
		if (vm.count("help") || !vm.count("work-dir")) {
			std::cerr << USAGE << visible_opts << std::endl << std::flush;
			return EXIT_FAILURE;
		}
		
		// Working directory
		fs::path data_dir(workdir);
		if (!fs::is_directory(workdir)) {
			std::cerr << SELF << ": working directory not found" 
				<< std::endl << std::flush;
			return EXIT_FAILURE;
		}

		std::cerr << "filename_text -> " << filename_text << std::endl;
		std::cerr << "filename_sa -> " << filename_sa << std::endl;
		std::cerr << "filename_lcp -> " << filename_lcp << std::endl;

		/*
		// input text filename and length
		
		std::string filename_text( vm["input-text"].as<std::string>() );
		struct stat stat_buf;
		int rc = stat(filename_text.c_str(), &stat_buf);
		if (rc != 0) {
			throw std::runtime_error("could not stat input text file");
		}
		long len = (rc == 0 ? stat_buf.st_size : -1);

		// type limits
		if (len > ((1 << 32) - 1)) {
			std::cerr << SELF << ": input file too large (max 4 GiB)" 
					<< std::endl << std::flush;
			return EXIT_FAILURE;
		}

		// memory map input text file
		boost::iostreams::mapped_file_source in_text;
		try {
			in_text.open(filename_text, (uint32)len);
		} catch (...) { }
		if (!in_text.is_open()) {
			throw std::runtime_error("could not map input text file");
		}
		char * text = (char *)in_text.data();

		// run map
		if (vm.count["map"]) {
			// naive algorithm split
			Context c(infile, param, h, t, workdir, name, id, keys, rs, text);
		}
		// run reduce
		else {
		}
		*/


		std::cerr << SELF << ": done" << std::endl;

		///in_text.close();
	}
	catch (std::exception& e) {
		std::cerr << SELF << ": " << e.what() << std::endl << std::flush;
		return EXIT_FAILURE;
	}
	catch (...) {
		std::cerr << SELF << ": caught unknown exception" 
			<< std::endl << std::flush;
		return EXIT_FAILURE;
	}

	std::cout << std::flush;
	std::cerr << std::flush;

	return EXIT_SUCCESS;
}

// vim:set ts=4 sts=4 sw=4 noexpandtab:
