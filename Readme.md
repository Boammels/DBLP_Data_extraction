This is a series program for DBLP extraction.
It will produce two json files in the parent folder.

### Including:

authors.json is a json file to remember all the researchers who have cooperated with others in the dblp database.

tempGraph.json stores the temporal information about the cooperation of the researchers. An edge between two authors refers to a cooperation according to the papers in DBLP and the time stamp associated is the year the paper was published.

### Usage:
1. Download the dblp.xml from https://dblp.org/xml/ and store it in the 2.root folder here.
2. Run the shell script generate.sh by
        ./generate.sh
or
        bash ./generate.sh

### Notice
This provides the data file for the TemporalEgoKCoreDemo repository.
Please check https://github.com/Boammels/TemporalEgoKCoreDemo for more information
