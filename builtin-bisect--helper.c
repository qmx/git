#include "builtin.h"
#include "cache.h"
#include "parse-options.h"
#include "bisect.h"

static const char * const git_bisect_helper_usage[] = {
	"git bisect--helper --next-vars",
	"git bisect--helper --next-exit",
	NULL
};

int cmd_bisect__helper(int argc, const char **argv, const char *prefix)
{
	int next_vars = 0;
	int next_exit = 0;
	struct option options[] = {
		OPT_BOOLEAN(0, "next-vars", &next_vars,
			    "output next bisect step variables"),
		OPT_BOOLEAN(0, "next-exit", &next_exit,
			    "output bisect result and exit instuctions"),
		OPT_END()
	};

	argc = parse_options(argc, argv, options, git_bisect_helper_usage, 0);

	if ((next_vars && next_exit) || (!next_vars && !next_exit))
		usage_with_options(git_bisect_helper_usage, options);

	if (next_vars)
		return bisect_next_vars(prefix);
	else /* next-exit */
		return bisect_next_exit(prefix);
}
