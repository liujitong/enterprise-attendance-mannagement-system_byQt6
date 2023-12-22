--员工编号（5位数字）、员工名（中文姓名或英文姓名）、登陆密码（8位以上）、部门、性别（从下拉列表选择“男”或“女”）、联系电话（11或12位数字组成）
CREATE TABLE employee (
    eno char(5) NOT NULL PRIMARY KEY,
    ename varchar(10) NOT NULL,
    dno char(3),
    gendar char(2),
    telephone char(12),
)
ALTER TABLE employee DROP CONSTRAINT enamecheck
--员工姓名只能是中文或英文
ALTER TABLE employee ADD CONSTRAINT enamecheck
CHECK (ename  not like '%[^吖-座]%');
--性别只能是男或女
ALTER TABLE employee ADD CONSTRAINT sexcheck
CHECK (gendar IN ('男','女'));
--联系电话11或12位数字组成
ALTER TABLE employee ADD CONSTRAINT telcheck
CHECK (len(telephone) IN (11,12));
--员工编号5位数字
ALTER TABLE employee ADD CONSTRAINT enocheck1
CHECK (eno LIKE '[0-9][0-9][0-9][0-9][0-9]');

ALTER TABLE account ADD CONSTRAINT enocheck12
CHECK (eno LIKE '[0-9][0-9][0-9][0-9][0-9]');

ALTER TABLE department ADD CONSTRAINT enocheck123
CHECK (dmano LIKE '[0-9][0-9][0-9][0-9][0-9]');

--登录密码八位以上:
ALTER TABLE account ADD CONSTRAINT psscheck
CHECK (len(code)>=8);

CREATE TABLE department(
    dno char(3)NOT NULL PRIMARY KEY,
    dname varchar(10) NOT NULL,
    dmano char(5) NOT NULL
)
--dname只能是中文
ALTER TABLE department ADD CONSTRAINT dnamecheck
CHECK (dname not like '%[^吖-座]%');

ALTER TABLE department DROP CONSTRAINT dnamecheck;
--dno长度为3
ALTER TABLE department ADD CONSTRAINT dnocheck
CHECK (len(dno)=3);

INSERT INTO account VALUES('%1','%2','2');