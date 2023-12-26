# 企业考勤系统

## 系统架构

系统从登录开始，数据库存储其类型（type0->superadmin(最高操作权限),type1->admin(部门管理员，负责管理本系统).type2->user(普通用户)）;

部门管理员进入系统的时候，会通过eno,dno两个标识，来区分其部门，变量名是：this_eno,this_dno;
