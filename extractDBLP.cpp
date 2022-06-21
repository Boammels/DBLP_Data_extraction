#include<stdio.h>
#include<stdlib.h>
#include<vector>
#include<string>
#include<map>

#define minimumCommonPaperNumber 3
#define dataLimit 0

using namespace std;

int main()
{
	char fdblp[] = "./dblp.xml";
	char fauthors[] = "./dblp_authors3.txt";
	char fpapers[] = "./dblp_papers3.txt";
	char faupaper[] = "./dblp_au_paper3.txt";
	char faurelation[] = "./dblp_au_relation3.txt";

	FILE *fd = NULL;
	FILE *fa = NULL;
	FILE *fp = NULL;
	FILE *fap = NULL;
	FILE *far = NULL;

	fd = fopen(fdblp, "r");
	fa = fopen(fauthors, "w");
	far = fopen(faurelation, "w");

	long count = 0;

	if (fd == NULL || fa == NULL || far == NULL)
	{
		printf("ERROR!");
		exit(1);
	}
	else
	{
		map<vector<char>, long> authorsMap;
		map<vector<char>, long> papersMap;
		vector<map<long, long> > authorRelationMap;
		vector<vector<char> > authors;
		vector<vector<char> > papers;
		vector<vector<long> > author_paper;
		vector<vector<long> > author_relation, author_relation_num;

		map<long, long> emptyMap;
		vector<char> curString, auName, paperName;
		vector<long> authorsList, empty;
		vector<char> end, booktitle, year, author;
		char ch;
		end.push_back('/');end.push_back('d');end.push_back('b');end.push_back('l');end.push_back('p');
		booktitle.push_back('b'); booktitle.push_back('o'); booktitle.push_back('o'); booktitle.push_back('k'); booktitle.push_back('t'); booktitle.push_back('i'); booktitle.push_back('t'); booktitle.push_back('l'); booktitle.push_back('e');
		year.push_back('y'); year.push_back('e'); year.push_back('a'); year.push_back('r');
		author.push_back('a'); author.push_back('u'); author.push_back('t'); author.push_back('h'); author.push_back('o'); author.push_back('r');

		curString.clear();
		long authorsMapID = 0;
		long papersMapID = 0;
		map<vector<char>, long>::iterator iter;
		map<long, long>::iterator iter1;
		vector<char> writeTemp;
		int check = 0;

		while (curString != end) //unique end tag
		{
			while (curString != author)
			{
				curString.clear();
				ch = getc(fd);
				while (ch != '<')
				{
					ch = getc(fd);
				}
				ch = getc(fd);
				while (ch != '>')
				{
					curString.push_back(ch);
					ch = getc(fd);
				}
				if (curString == end)
				{
					break;
				}
			}
			if (curString == end)
			{
				break;
			}
			authorsList.clear();
			while (curString == author)
			{
				auName.clear();
				ch = getc(fd);
				while (ch != '<')
				{
					auName.push_back(ch);
					ch = getc(fd);
				}
				bool authorExist = 0;
				iter = authorsMap.find(auName);
				if (iter == authorsMap.end())
				{
					authorsList.push_back(authorsMapID);
					authorsMap.insert(pair<vector<char>, long>(auName, authorsMapID));
					authorsMapID++;
					authors.push_back(auName);
					author_paper.push_back(empty);
					author_relation.push_back(empty);
					author_relation_num.push_back(empty);
					authorRelationMap.push_back(emptyMap);
				}
				else
				{
					authorsList.push_back(iter->second);
				}
				ch = getc(fd);
				while (ch != '<')
				{
					ch = getc(fd);
				}
				ch = getc(fd);
				curString.clear();
				while (ch != '>')
				{
					curString.push_back(ch);
					ch = getc(fd);
				}
			}
			if (authorsList.size() > 1)
			{
				check = 1;
				for (long i = 0; i < authorsList.size(); i++)
				{
					long auID = authorsList[i];
					for (long j = 0; j < authorsList.size(); j++)
					{
						long auID1 = authorsList[j];
						if (auID1 != auID)
						{
							writeTemp.clear();
							long authorID = auID1;
							while (1)
							{
								char c = char(authorID % 10 + '0');
								authorID /= 10;
								writeTemp.insert(writeTemp.begin(), c);
								if (authorID == 0)
								{
									break;
								}
							}
							for (long k = 0; k < writeTemp.size(); k++)
							{
								ch = putc(writeTemp[k], far);
							}
							ch = putc(' ', far);
							writeTemp.clear();
							long paperID = auID;
							while (1)
							{
								char c = char(paperID % 10 + '0');
								paperID /= 10;
								writeTemp.insert(writeTemp.begin(), c);
								if (paperID == 0)
								{
									break;
								}
							}
							for (long k = 0; k < writeTemp.size(); k++)
							{
								ch = putc(writeTemp[k], far);
							}
							ch = putc('\n', far);
						}
					}
				}
			}
			while (curString != year && curString != author)
			{
				curString.clear();
				ch = getc(fd);
				while (ch != '<')
				{
					ch = getc(fd);
				}
				ch = getc(fd);
				while (ch != '>')
				{
					curString.push_back(ch);
					ch = getc(fd);
				}
				if (curString == end)
				{
					break;
				}
			}
			if (curString == end)
			{
				break;
			}
			if (curString != author && check == 1)
			{
				paperName.clear();
				putc('\'', far);
				ch = getc(fd);
				while (ch != '<')
				{
					ch = putc(ch, far);
					ch = getc(fd);
				}
				ch = putc('\n',far);
				check = 0;
			}
			count++;
			if (count >= 1000 && count % 1000 == 0)
			{
				printf("new %ld processed\n", count);
			}
			if (dataLimit && count > dataLimit)
			{
				break;
			}
			if (check == 1) {
				putc('\'', far);
				putc('\n', far);
				check = 0;
			}
		}
		//write to authors.txt
		for (long i = 0; i < authors.size(); i++)
		{
			writeTemp.clear();
			long authorID = i;
			while (1)
			{
				char c = char(authorID % 10 + '0');
				authorID /= 10;
				writeTemp.insert(writeTemp.begin(), c);
				if (authorID == 0)
				{
					break;
				}
			}
			for (long j = 0; j < writeTemp.size(); j++)
			{
				ch = putc(writeTemp[j], fa);
			}
			ch = putc('\t', fa);
			for (long j = 0; j < authors[i].size(); j++)
			{
				ch = putc(authors[i][j], fa);
			}
			ch = putc('\n', fa);
		}
		for (long i = 0; i < author_relation.size(); i++)
		{
			for (long j = 0; j < author_relation[i].size(); j++)
			{
				if (author_relation_num[i][j] >= minimumCommonPaperNumber)
				{
					writeTemp.clear();
					long authorID = i;
					
				}
			}
		}
	}

	fclose(fd);
	fclose(fa);
	fclose(far);
	return 0;
}
