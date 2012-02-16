#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <ulib/list.h>
#include <ulib/log.h>

struct str_ent {
	struct list_head aaa;
	char *str;
};

void line2list(struct list_head *head, const char *file)
{
	FILE *fp;
	struct str_ent *p;
	char *line = NULL;
	size_t n;
	int nl = 0;

	fp = fopen(file, "r");
	if (fp == NULL) {
		ULIB_FATAL("cannot open %s", file);
		exit(EXIT_FAILURE);
	}
	while (getline(&line, &n, fp) > 0) {
		p = (struct str_ent *) malloc(sizeof(struct str_ent));
		if (p == NULL) {
			ULIB_FATAL("cannot new entry");
			exit(EXIT_FAILURE);
		}
		list_add_tail(&p->aaa, head);
		p->str = line;
		line = NULL;
		++nl;
	}
	free(line);
	fclose(fp);
	ULIB_NOTICE("%d line(s) has been loaded", nl);
}
/*
void myline2list(struct list_head *head, const char *file)
{
	FILE *fp;
	struct str_ent *p;
	char line[1024];
	size_t n;
	int nl = 0;
	int size = 1024;
	
	memset(line, '\0', sizeof(line));

	fp = fopen(file, "r");
	if (fp == NULL) {
		ULIB_FATAL("cannot open %s", file);
		exit(EXIT_FAILURE);
	}
	while (fgets(line, size, fp) > 0) {
		p = (struct str_ent *) malloc(sizeof(struct str_ent));
		if (p == NULL) {
			ULIB_FATAL("cannot new entry");
			exit(EXIT_FAILURE);
		}
		list_add_tail(&p->link, head);
		p->str = line;
	//	line = NULL;
		memset(line, '\0', sizeof(line));
		++nl;
	}
	//free(line);
	fclose(fp);
	ULIB_NOTICE("%d line(s) has been loaded", nl);
}
*/

void free_list(struct list_head *head)
{
	struct str_ent *p, *n;

	list_for_each_entry_safe(p, n, head, aaa) {
		free(p->str);
		free(p);
	}
}

int main(int argc, char *argv[])
{
	LIST_HEAD(str_lst);

	if (argc != 2) {
		ULIB_FATAL("usage: %s file", argv[0]);
		return -1;
	}

	line2list(&str_lst, argv[1]);
	free_list(&str_lst);

	return 0;
}
