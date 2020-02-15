#include<string.h>    //调用字符串函数库
#include<stdlib.h>    //调用新运行库
#include <time.h>
#include <windows.h>
#include <iostream>
#include<stdio.h> //调用标准库
#include<winsock2.h>  //调用连接模式库
#include <mysql.h>
#define HOST "localhost"    //定义连接服务体
#define USERNAME "root"     //定义MySQL用户名
#define PASSWORD "syh7716"   //定义用户密码
#define DATABASE "gradeManager"      //定义连接数据库

using namespace std;

MYSQL mysql;    //定义连接，MYSQL必须大写
MYSQL *conn_prt;     //创造一个MYSQL句柄
MYSQL_RES *res;
MYSQL_ROW row;
char type;	//定义的用户类型
/*一些操作的命令起始部分*/
char select_head[50] = "select * from ";
char desc_head[50] = "desc ";
char insert_head[200] = "insert into ";
char drop_msg_head[50] = "delete from ";
char change_base_head[50] = "use ";


//初始化mysql句柄
void self_init()
{
    conn_prt = mysql_init(NULL);
}

//登陆主界面
void index();
//登陆后目录
void menu();
//判断登陆函数
bool login(char* userName,char* passWord);
//查询函数主目录
void query();
//课程查询
void classQuery();
//分数查询
void gradeQuery();
//更新函数主目录
void update();
//课程更新
void classUpdate();
//分数更新
void gradeUpdate();
//学生信息更新
void studentUpdate();
//教师信息更新
void teacherUpdate();
//添加函数主目录
void add();
//课程信息添加
void classAdd();
//分数信息添加
void gradeAdd();
//学生信息添加
void studentAdd();
//教师信息添加
void teacherAdd();
//退出系统
void logOut();

int main(){

    int res;
    mysql_init(&mysql); //连接
    mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");
    //连接条件
     //
    if( mysql_real_connect(&mysql,HOST,USERNAME,PASSWORD,DATABASE,0,NULL,CLIENT_FOUND_ROWS)){
        printf("连接成功,跳转中...");
    }
   	//_sleep(2000);
	index();

    return 0;
}

void menu()
{
	system("cls");
	int op;
	printf("\n\n\n\n");
	printf("\t\t\t\t -----------------------------------\n");
	printf("\t\t\t\t|           学生成绩查询系统        |\n");
	printf("\t\t\t\t -----------------------------------\n\n");
	printf("\t\t\t\t\t    1、信息查询\n\n");
	printf("\t\t\t\t\t    2、信息修改\n\n");
	printf("\t\t\t\t\t    3、信息添加\n\n");
	printf("\t\t\t\t\t    4、退出登录\n\n");
	printf("\t\t\t\t\t    5、结束程序\n\n");
	printf("\t\t\t\t\t    请输入需要进行的操作：");
	cin>>op;
	if (op == 1)
		query();
	if (op == 2)
		update();
	if (op == 3)
		add();
	if (op == 4)
		index();
	if (op == 5)
		logOut();
}

void index()
{
	char userName[12];
	char passWord[12];
	system("cls");
	printf("\n\n\n\n");
	printf("\t\t\t\t -----------------------------------\n");
	printf("\t\t\t\t|           学生成绩查询系统        |\n");
	printf("\t\t\t\t -----------------------------------\n\n");
	printf("\t\t\t\t\t请输入用户名：");
	cin>>userName;
	printf("\n\t\t\t\t\t请输入密码：");
	cin>>passWord;
	//实现登陆
	if(login(userName,passWord))
		menu();
	else
	{
		index();
	}
}

bool login(char* userName,char* passWord)
{
	int t;
	char User[12] = "";
	char psw[12] = "";
	strcpy(User,userName);
	strcpy(psw,passWord);
	char sqlLog[100] = "select userpsw,usertype from UserInfo where username = \"";
	strcat(sqlLog,User);
	strcat(sqlLog,"\";");
//	cout<<sqlLog<<endl;
	t = mysql_query(&mysql,sqlLog);
    if(t)
    {
        printf("failed to LogIn:%s\n",mysql_error(&mysql));
        index();
    }
    res = mysql_store_result(&mysql);
    if((row = mysql_fetch_row(res)) != NULL)
    {
    	char psw[12];
    	strcpy(psw,row[0]);
		type = *row[1];
		if (!strcmp(passWord,psw))
	    {
	    	system("cls");
			printf("\n\n\n\n");
			printf("\t\t\t\t -----------------------------------\n");
			printf("\t\t\t\t|           学生成绩查询系统        |\n");
			printf("\t\t\t\t -----------------------------------\n\n");
			printf("\t\t\t\t\t登陆成功!正在跳转...");
			_sleep(2000);
			return true;
		}
		else
		{
			system("cls");
			printf("\n\n\n\n");
			printf("\t\t\t\t -----------------------------------\n");
			printf("\t\t\t\t|           学生成绩查询系统        |\n");
			printf("\t\t\t\t -----------------------------------\n\n");
			printf("\t\t\t\t密码或用户名错误！");
			_sleep(2000);
			return false;
		}

    }
    else{
    	return false;
	}

}

void query()
{
	system("cls");
	int op;
	printf("\n\n\n\n");
	printf("\t\t\t\t -----------------------------------\n");
	printf("\t\t\t\t|           学生成绩查询系统        |\n");
	printf("\t\t\t\t -----------------------------------\n\n");
	printf("\t\t\t\t\t    1、课程查询\n\n");
	printf("\t\t\t\t\t    2、成绩查询\n\n");
	printf("\t\t\t\t\t    3、返回\n\n");
	printf("\t\t\t\t\t    请输入需要进行的操作：");

	cin>>op;
	if (op == 1)
		classQuery();
	if (op == 2)
		gradeQuery();
	printf("\n\t\t\t\t");
	if (op == 3)
		menu();


}
//课程查询
void classQuery()
{
	//如果是管理员
	if (type == '1')
	{
		system("cls");
		int op;
		printf("\n\n\n\n");
		printf("\t\t\t\t -----------------------------------\n");
		printf("\t\t\t\t|           学生成绩查询系统        |\n");
		printf("\t\t\t\t -----------------------------------\n\n");
		printf("\t\t\t\t\t请输入查询对象（1->学生，2->老师，3->返回）：");
		printf("\n\t\t\t\t");
		cin>>op;
		//若操作码为1
		if (op == 1)
		{
			system("cls");
			int t;
			char name[15];
			printf("\n\n\n\n");
			printf("\t\t\t\t -----------------------------------\n");
			printf("\t\t\t\t|              学生信息表           |\n");
			printf("\t\t\t\t -----------------------------------\n\n");
			char sqlLog[100] = "select sid,sname,scollege,sdep from student ";
			t = mysql_query(&mysql,sqlLog);
		    if(t)
		    {
		        printf("failed to LogIn:%s\n",mysql_error(&mysql));

		    }
		    res = mysql_store_result(&mysql);
		    while( (row = mysql_fetch_row(res)) )
	        {
	            //遍历字段
	            for(int i=0 ; i <  res->field_count; i++)
	            {
	                //打印字段值
	                //在这里可以赋值给其它变量
	               	printf("\t\t");
                	printf("%-5s ",row[i]);
            	}
            	printf("\n");
	        }
	        //释放，不要忘记
	        mysql_free_result(res);
	        _sleep(5000);
			classQuery();
		}
		//若操作码为2
		if (op == 2)
		{
			system("cls");
			int t;
			char name[15];
			printf("\n\n\n\n");
			printf("\t\t\t\t -----------------------------------\n");
			printf("\t\t\t\t|              教师信息表           |\n");
			printf("\t\t\t\t -----------------------------------\n\n");

			char sqlLog[100] = "select tid,tname,tcollege,tdep from teacher ";
	//	cout<<sqlLog<<endl;
			t = mysql_query(&mysql,sqlLog);
			mysql_query(&mysql,"set names utf8");   //字符集处理
		    if(t)
		    {
		        printf("failed to LogIn:%s\n",mysql_error(&mysql));

		    }
		    res = mysql_store_result(&mysql);
		    while( (row = mysql_fetch_row(res)) )
	        {
	            //遍历字段
	            for(int i=0 ; i <  res->field_count; i++)
	            {
	                //打印字段值
	                //在这里可以赋值给其它变量
	               printf("\t\t");
                	printf("%-5s ",row[i]);
            }
            printf("\n");
	        }
	        //释放，不要忘记
	        mysql_free_result(res);
	        _sleep(5000);
			classQuery();
		}
		if (op == 3)
		{
			query();
		}

	}
	if (type == '2')
	{
		int t;
		char Sname[10];
		system("cls");
		printf("\n\n\n\n");
		printf("\t\t\t\t -----------------------------------\n");
		printf("\t\t\t\t|           学生成绩查询系统        |\n");
		printf("\t\t\t\t -----------------------------------\n\n");
		printf("\t\t\t\t请输入学生姓名：");
		cin>>Sname;
		char sql_1[500] = "select sid,sname,cid,cname from student,classs  where sname = \"";
		strcat(sql_1,Sname);
		char sql_2[500] = " and sid in (select sid from select_class where cid in (select cid from classs))";
		strcat(sql_1,sql_2);
		t = mysql_query(&mysql,sql_1);
		if(t)
		{
	        printf("failed to LogIn:%s\n",mysql_error(&mysql));
		}
	    res = mysql_store_result(&mysql);
	    while( (row = mysql_fetch_row(res)) )
	    {
            //遍历字段
            for(int i=0 ; i <  res->field_count; i++)
            {
                //打印字段值
                //在这里可以赋值给其它变量
                printf("\t\t");
                printf("%-5s ",row[i]);
            }
            printf("\n");
        }
        //释放，不要忘记
        mysql_free_result(res);
		_sleep(5000);
		query();
	}

	if (type == '3')
	{
		char Tname[10];
		int t;
		system("cls");
		printf("\n\n\n\n");
		printf("\t\t\t\t -----------------------------------\n");
		printf("\t\t\t\t|           学生成绩查询系统        |\n");
		printf("\t\t\t\t -----------------------------------\n\n");
		printf("\t\t\t\t请输入学生姓名：");
		cin>>Tname;
		char sql_1[500] = "select tid,tname,cid,cname from teacher,classs  where tname = \"";
		strcat(sql_1,Tname);
		char sql_2[500] = " and tid in (select tid from take_class  where cid in (select cid from classs))";
		strcat(sql_1,sql_2);
		t = mysql_query(&mysql,sql_1);
		if(t)
		{
	        printf("failed to LogIn:%s\n",mysql_error(&mysql));
		}
	    res = mysql_store_result(&mysql);
	    while( (row = mysql_fetch_row(res)) )
	    {
            //遍历字段
            for(int i=0 ; i <  res->field_count; i++)
            {
                //打印字段值
                //在这里可以赋值给其它变量
                printf("\t\t");
                printf("%-5s ",row[i]);
            }
            printf("\n");
        }
        _sleep(5000);
		query();

        //释放，不要忘记
        mysql_free_result(res);
	}

}
void gradeQuery()
{
	if (type == '1')
	{
		system("cls");
		int t;
		printf("\n\n\n\n");
		printf("\t\t\t\t -----------------------------------\n");
		printf("\t\t\t\t|              学生信息表           |\n");
		printf("\t\t\t\t -----------------------------------\n\n");
		printf("\t\t\t\t\t");
		char sqlLog[500] = "select student.sid,sname,grade from student,select_class where student.sid in (select sid from select_class );";
	//	cout<<sqlLog<<endl;
		t = mysql_query(&mysql,sqlLog);
	    if(t)
	    {
	        printf("failed to LogIn:%s\n",mysql_error(&mysql));
	    }
	    res = mysql_store_result(&mysql);
	    while( (row = mysql_fetch_row(res)) )
        {
            //遍历字段
            for(int i=0 ; i <  res->field_count; i++)
            {
                //打印字段值
                //在这里可以赋值给其它变量
           		printf("\t\t");
                printf("%-5s ",row[i]);
            }
            printf("\n");
        }

        //释放，不要忘记
	    mysql_free_result(res);
	     _sleep(5000);
	    query();
	}
	if (type == '2')
	{
		int t;
		char Sname[10];
		system("cls");
		printf("\n\n\n\n");
		printf("\t\t\t\t -----------------------------------\n");
		printf("\t\t\t\t|           学生成绩查询系统        |\n");
		printf("\t\t\t\t -----------------------------------\n\n");
		printf("\t\t\t\t请输入学生姓名：");
		cin>>Sname;
		char sql_1[500] = "select student.sid,sname,grade from student,select_class where sname = \"";
		char sql_2[500] = "\"student.sid in (select sid from select_class );";
		strcat (sql_1,Sname);
		strcat (sql_1,sql_2);
	//	cout<<sqlLog<<endl;
		t = mysql_query(&mysql,sql_1);
	    if(t)
	    {
	        printf("failed to LogIn:%s\n",mysql_error(&mysql));
	    }
	    res = mysql_store_result(&mysql);
	    while( (row = mysql_fetch_row(res)) )
        {
            //遍历字段
            for(int i=0 ; i <  res->field_count; i++)
            {
                //打印字段值
                //在这里可以赋值给其它变量
                printf("\t\t");
                printf("%-5s ",row[i]);
            }
            printf("\n");
        }
        //释放，不要忘记
	    mysql_free_result(res);
	     _sleep(5000);
	    query();

	}
	if (type == '3')
	{
		char Tname[10];
		int t;
		system("cls");
		printf("\n\n\n\n");
		printf("\t\t\t\t -----------------------------------\n");
		printf("\t\t\t\t|           学生成绩查询系统        |\n");
		printf("\t\t\t\t -----------------------------------\n\n");
		printf("\t\t\t\t请输入老师姓名：");
		cin>>Tname;
		char sql_1[500] = "select tname,student.sid,sname,classs.cname,grade from teacher,student,classs,select_class where tname = \"";
		char sql_2[500] = "\" and tid in (select tid from take_class where cid in (select cid from select_class where sid in (select sid from student)))";
		strcat (sql_1,Tname);
		strcat (sql_1,sql_2);
	//	cout<<sqlLog<<endl;
		t = mysql_query(&mysql,sql_1);
	    if(t)
	    {
	        printf("failed to LogIn:%s\n",mysql_error(&mysql));
	    }
	    res = mysql_store_result(&mysql);
	    while( (row = mysql_fetch_row(res)) )
        {
            //遍历字段
            for(int i=0 ; i <  res->field_count; i++)
            {
                //打印字段值
                //在这里可以赋值给其它变量
                printf("\t\t");
                printf("%-5s ",row[i]);
            }
            printf("\n");
        }
		//释放，不要忘记
	    mysql_free_result(res);
	     _sleep(5000);
	    query();
	}
}

void update()
{
	system("cls");
	int op;
	printf("\n\n\n\n");
	printf("\t\t\t\t -----------------------------------\n");
	printf("\t\t\t\t|           学生成绩查询系统        |\n");
	printf("\t\t\t\t -----------------------------------\n\n");
	printf("\t\t\t\t\t1、课程信息修改\n\n");
	printf("\t\t\t\t\t2、成绩信息修改\n\n");
	printf("\t\t\t\t\t3、学生信息修改\n\n");
	printf("\t\t\t\t\t4、老师信息修改\n\n");
	printf("\t\t\t\t\t5、返回\n\n");
	printf("\t\t\t\t\t请输入需要进行的操作：");
	cin>>op;
	if (op == 1 and type == '1')
		classUpdate();
	else if (op == 2 and (type == '1' or type == '3'))
		gradeUpdate();
	else if (op == 3 and type == '1')
		studentUpdate();
	else if (op == 4 and type == '1')
		teacherUpdate();
	else if (op == 5)
		menu();
	else
	{
		system("cls");
		printf("\n\n\n\n");
		printf("\t\t\t\t -----------------------------------\n");
		printf("\t\t\t\t|           学生成绩查询系统        |\n");
		printf("\t\t\t\t -----------------------------------\n\n");
		printf ("\t\t\t\t您没有操作权限！");
		_sleep(1500);
		update();
	}
}

void classUpdate()
{
	char cid[19];
	char cname[19];
	system("cls");
	printf("\n\n\n\n");
	printf("\t\t\t\t -----------------------------------\n");
	printf("\t\t\t\t|           学生成绩查询系统        |\n");
	printf("\t\t\t\t -----------------------------------\n\n");
	printf ("\t\t\t请输入需更改的课程号：");
	cin>>cid;
	printf ("\n\t\t\t请输入新的课程名:");
	cin>>cname;
	char sql_1[500] = "update classs set cname = \"";
	char sql_2[100] = "\" where cid = \"";
	char sql_3[100] = "\"";
	strcat (sql_1,cname);
	strcat (sql_1,sql_2);
	strcat (sql_1,cid);
	strcat (sql_1,sql_3);
	 //更新修改mysql数据表的条目
	if( mysql_query( &mysql , sql_1 ) )
	{
	printf("修改数据表条目失败!");//打印出错误代码及详细信息
	}
	else//成功
	{
	printf("修改数据表条目成功!");//输出受影响的行数
	}
	_sleep(1100);
	update();
}
void gradeUpdate()
{
	char cid[19];
	char sid[19];
	char grade[5];
	system("cls");
	printf("\n\n\n\n");
	printf("\t\t\t\t -----------------------------------\n");
	printf("\t\t\t\t|           学生成绩查询系统        |\n");
	printf("\t\t\t\t -----------------------------------\n\n");
	printf ("\t\t\t请输入课程号：");
	cin>>cid;
	printf ("\n\t\t\t请输入学号：");
	cin>>sid;
	printf ("\n\t\t\t请输入新的成绩：");
	cin>>grade;
	char sql_1[500] = "update select_class set grade = \"";
	char sql_2[100] = "\" where cid = \"";
	char sql_3[100] = "\" and sid = \"";
	char sql_4[100] = "\"";
	strcat (sql_1,grade);
	strcat (sql_1,sql_2);
	strcat (sql_1,cid);
	strcat (sql_1,sql_3);
	strcat (sql_1,sid);
	strcat (sql_1,sql_4);
	 //更新修改mysql数据表的条目
	if( mysql_query( &mysql , sql_1 ) )
	{
	printf("修改数据表条目失败!");//打印出错误代码及详细信息
	}
	else//成功
	{
	printf("修改数据表条目成功 !");//输出受影响的行数
	}
	_sleep(1000);
	update();
}
void studentUpdate()
{

//	update student set scollege = \"信科院\",sdep = \"计算机科学\" where sid = \"00001\" ;
	char sid[19];
	char scollege[20];
	char sdep[20];
	system("cls");
	printf("\n\n\n\n");
	printf("\t\t\t\t -----------------------------------\n");
	printf("\t\t\t\t|           学生成绩查询系统        |\n");
	printf("\t\t\t\t -----------------------------------\n\n");
	printf ("\t\t\t请输入学号：");
	cin>>sid;
	printf ("\n\t\t\t请输入新学院：");
	cin>>scollege;
	printf ("\n\t\t\t请输入新系：");
	cin>>sdep;
	char sql_1[500] = "update student set scollege = \"";
	char sql_2[100] = "\",sdep = \"";
	char sql_3[100] = "\" where sid = \"";
	char sql_4[100] = "\"";
	strcat (sql_1,scollege);
	strcat (sql_1,sql_2);
	strcat (sql_1,sdep);
	strcat (sql_1,sql_3);
	strcat (sql_1,sid);
	strcat (sql_1,sql_4);
	 //更新修改mysql数据表的条目
	if( mysql_query( &mysql , sql_1 ) )
	{
	printf("修改数据表条目失败!");//打印出错误代码及详细信息
	}
	else//成功
	{
	printf("修改数据表条目成功!");//输出受影响的行数
	}
	_sleep(1000);
	update();
}
void teacherUpdate()
{
	char tid[19];
	char tcollege[20];
	char tdep[20];
	system("cls");
	printf("\n\n\n\n");
	printf("\t\t\t\t -----------------------------------\n");
	printf("\t\t\t\t|           学生成绩查询系统        |\n");
	printf("\t\t\t\t -----------------------------------\n\n");
	printf ("\t\t\t请输入工号：");
	cin>>tid;
	printf ("\n\t\t\t请输入学院：");
	cin>>tcollege;
	printf ("\n\t\t\t请输入系：");
	cin>>tdep;
	char sql_1[500] = "update teacher set scollege = \"";
	char sql_2[100] = "\",tdep = \"";
	char sql_3[100] = "\" where tid = \"";
	char sql_4[100] = "\"";
	strcat (sql_1,tcollege);
	strcat (sql_1,sql_2);
	strcat (sql_1,tdep);
	strcat (sql_1,sql_3);
	strcat (sql_1,tid);
	strcat (sql_1,sql_4);
	 //更新修改mysql数据表的条目
	if( mysql_query( &mysql , sql_1 ) )
	{
	printf("修改数据表条目失败!");//打印出错误代码及详细信息
	}
	else//成功
	{
	printf("修改数据表条目成功!");//输出受影响的行数
	}
	_sleep(1000);
	update();
}

void add()
{
	int op;
	system("cls");
	printf("\n\n\n\n");
	printf("\t\t\t\t -----------------------------------\n");
	printf("\t\t\t\t|           学生成绩查询系统        |\n");
	printf("\t\t\t\t -----------------------------------\n\n");
	printf("\t\t\t\t\t1、课程信息添加\n\n");
	printf("\t\t\t\t\t2、成绩信息修改\n\n");
	printf("\t\t\t\t\t3、学生信息添加\n\n");
	printf("\t\t\t\t\t4、老师信息添加\n\n");
	printf("\t\t\t\t\t5、返回目录\n\n");
	printf("\t\t\t\t\t请输入需要进行的操作：\n\n");
	cin>>op;
	if (op == 1 and type == '1')
		classAdd();
	if (op == 2 and (type == '1' or type == '3'))
		gradeAdd();
	if (op == 3 and (type == '1' or type == '3'))
		studentAdd();
	if (op == 4 and type == '1')
		teacherAdd();
	if (op == 5)
		menu();
}

void classAdd()
{
	//insert into classs values("00006","高等数学");
	char cid[10];
	char cname[30];
	int t;
	system("cls");
	printf("\n\n\n\n");
	printf("\t\t\t\t -----------------------------------\n");
	printf("\t\t\t\t|           学生成绩查询系统        |\n");
	printf("\t\t\t\t -----------------------------------\n\n");
	printf("\t\t\t\t 请输入课程号：\n\n");
	cin>>cid;
	printf("\t\t\t\t 请输入课程成绩：\n\n");
	cin>>cname;
	char sql_1[400] = "insert into classs values(\"";
	char sql_2[100] = "\",\"";
	char sql_3[100] = "\")";
	strcat(sql_1,cid);
	strcat(sql_1,sql_2);
	strcat(sql_1,cname);
	strcat(sql_1,sql_3);
	t = mysql_real_query(conn_prt,sql_1,strlen(sql_1));
    if(t)
    {
        printf("failed to query:%s\n",mysql_error(conn_prt));
        return ;
    }
    printf("添加成功！\n");
	_sleep(1000);
	add();
}
void gradeAdd()
{
//	insert into select_class values("0001","0001","30");
	char cid[10];
	char sid[10];
	char grade[5];
	int t;
	system("cls");
	printf("\n\n\n\n");
	printf("\t\t\t\t -----------------------------------\n");
	printf("\t\t\t\t|           学生成绩查询系统        |\n");
	printf("\t\t\t\t -----------------------------------\n\n");
	printf("\t\t\t\t 请输入课程号：\n\n");
	cin>>cid;
	printf("\t\t\t\t 请输入学号：\n\n");
	cin>>sid;
	printf("\t\t\t\t 请输入课程成绩：\n\n");
	cin>>grade;
	char sql_1[400] = "insert into select_class values(\"";
	char sql_2[100] = "\",\"";
	char sql_3[100] = "\")";
	strcat(sql_1,cid);
	strcat(sql_1,sql_2);
	strcat(sql_1,sid);
	strcat(sql_1,sql_2);
	strcat(sql_1,grade);
	strcat(sql_1,sql_3);
	t = mysql_real_query(conn_prt,sql_1,strlen(sql_1));
    if(t)
    {
        printf("failed to query:%s\n",mysql_error(conn_prt));
        return ;
    }
    printf("添加成功！\n");
	_sleep(1000);
	add();
}
void studentAdd()
{

	char sname[10];
	char sid[10];
	char scollege[20];
	char sdep[20];
	int t;
	system("cls");
	printf("\n\n\n\n");
	printf("\t\t\t\t -----------------------------------\n");
	printf("\t\t\t\t|           学生成绩查询系统        |\n");
	printf("\t\t\t\t -----------------------------------\n\n");
	printf("\t\t\t\t 请输入姓名：\n\n");
	cin>>sname;
	printf("\t\t\t\t 请输入学号：\n\n");
	cin>>sid;
	printf("\t\t\t\t 请输入学院：\n\n");
	cin>>scollege;
	printf("\t\t\t\t 请输入所在系：\n\n");
	cin>> sdep;
//	insert into teacher values("陈天宇","0052","2","信息院","计算机系");
	char sql_1[400] = "insert into student values(\"";
	char sql_2[100] = "\",\"";
	char sql_3[100] = "\")";
	char sql_4[100] = "\",\"2\",\"";
	strcat(sql_1,sname);
	strcat(sql_1,sql_2);
	strcat(sql_1,sid);
	strcat(sql_1,sql_4);
	strcat(sql_1,scollege);
	strcat(sql_1,sql_2);
	strcat(sql_1,sdep);
	strcat(sql_1,sql_3);
	t = mysql_real_query(conn_prt,sql_1,strlen(sql_1));
    if(t)
    {
        printf("failed to query:%s\n",mysql_error(conn_prt));
        return ;
    }
    printf("添加成功！\n");
	_sleep(1000);
	add();
}
void teacherAdd()
{

	char tname[10];
	char tid[10];
	char tcollege[20];
	char tdep[20];
	int t;
	system("cls");
	printf("\n\n\n\n");
	printf("\t\t\t\t -----------------------------------\n");
	printf("\t\t\t\t|           学生成绩查询系统        |\n");
	printf("\t\t\t\t -----------------------------------\n\n");
	printf("\t\t\t\t 请输入姓名：\n\n");
	cin>>tname;
	printf("\t\t\t\t 请输入工号：\n\n");
	cin>>tid;
	printf("\t\t\t\t 请输入学院：\n\n");
	cin>>tcollege;
	printf("\t\t\t\t 请输入所在系：\n\n");
	cin>> tdep;
//	insert into teacher values("戴小鹏","0012","2","信息院","计算机系");
	char sql_1[400] = "insert into teacher values(\"";
	char sql_2[100] = "\",\"";
	char sql_3[100] = "\")";
	char sql_4[100] = "\",\"3\",\"";
	strcat(sql_1,tname);
	strcat(sql_1,sql_2);
	strcat(sql_1,tid);
	strcat(sql_1,sql_4);
	strcat(sql_1,tcollege);
	strcat(sql_1,sql_2);
	strcat(sql_1,tdep);
	strcat(sql_1,sql_3);
	t = mysql_real_query(conn_prt,sql_1,strlen(sql_1));
    if(t)
    {
        printf("failed to query:%s\n",mysql_error(conn_prt));
        return ;
    }
    printf("添加成功！\n");
	_sleep(1000);
	add();
}
void logOut ()
{
	system("cls");
	printf("\n\n\n\n");
	printf("\t\t\t系统已关闭！\n\n\n\n");
	exit(0);
}



