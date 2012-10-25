#library("svn");

#import("dart-ext:dart_svn");

string getVersion()  native "Version";
class SvnVersion
{
	static int major = 1;
	static int minor = 7;
	static int patch = 6;
}

class SVN
{
}
