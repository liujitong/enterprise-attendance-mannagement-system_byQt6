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
CHECK (ename  not like '%[^吖-座]%|[^a-z]%|[^A-Z]%');
--性别只能是男或女
ALTER TABLE employee ADD CONSTRAINT sexcheck
CHECK (gendar IN ('男','女'));
--联系电话11或12位数字组成
ALTER TABLE employee ADD CONSTRAINT telcheck
CHECK (len(telephone) IN (11,12));
--员工编号5位数字
ALTER TABLE employee ADD CONSTRAINT enocheck1
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

UPDATE account SET code='12345678' WHERE eno='00001';
--获取部门编号，名称，其员工数量，管理员姓名和备注
SELECT d.dno, d.dname, (SELECT COUNT(*) FROM employee WHERE dno = d.dno) AS '员工数量', e.ename AS '管理员姓名', d.Other AS '备注'
FROM department d
LEFT JOIN employee e ON d.dmano = e.eno
GROUP BY d.dno, d.dname, e.ename, d.Other;
GO
CREATE TRIGGER insert_employee
ON employee
FOR INSERT
AS
BEGIN
    INSERT INTO account VALUES((SELECT eno FROM inserted),'12345678','2');
END
GO
--设计一个触发器，当删除一个员工的时候，自动删除其账户
CREATE TRIGGER delete_employee
ON employee
FOR DELETE
AS
BEGIN
    DELETE FROM account WHERE eno=(SELECT eno FROM deleted);
END
Go
--设计触发器，当删除一个部门的时候，将其员工的部门编号置为空，将部门管理员置的类型置为普通员工
CREATE TRIGGER delete_department
ON department
FOR DELETE
AS
BEGIN
    UPDATE employee SET dno=NULL WHERE dno=(SELECT dno FROM deleted);
    UPDATE account SET type='2' WHERE eno=(SELECT dmano FROM deleted);
END
GO
--将部门编号为002的部门管理员的类型设置为普通员工
UPDATE account SET type='2' WHERE eno=(SELECT dmano FROM department WHERE dno='002');
GO
--设计触发器，当部门被修改的时候，将部门管理员的dno置为修改后的部门编号
CREATE TRIGGER update_department
ON department
FOR UPDATE
AS
BEGIN
    UPDATE employee SET dno=(SELECT dno FROM inserted) WHERE eno=(SELECT dmano FROM deleted);
END
GO
--删除指定编号的部门
DELETE FROM department WHERE dno='002';

--找出所有部门为空的员工
SELECT * FROM employee WHERE dno IS NULL;

--查询所有员工的信息，如果该员工的部门编号为空，则显示“无部门”，否则显示部门名称
SELECT e.eno, e.ename, ISNULL(d.dname,'无部门') AS '部门名称', ISNULL(e.gendar,'N'), ISNULL(e.telephone,'待补充')
FROM employee e
LEFT JOIN department d ON e.dno = d.dno;
GO
--查询除员工号为%1的员工所在部门外的所有部门的名称和编号，同时，当该员工所在部门为空时，显示所有部门的名称和编号
SELECT d.dno, d.dname
FROM department d
WHERE d.dno NOT IN (SELECT dno FROM employee WHERE eno='00002')
UNION
SELECT d.dno, d.dname
FROM department d
WHERE d.dno IN (SELECT dno FROM employee WHERE eno='00002') AND d.dno IS NULL; 

--删除员工的时候，如果这个员工是部门管理员，则将其部门的管理员置为空
CREATE TRIGGER delete_employee_admin_set_null
ON employee
FOR DELETE
AS
BEGIN
    UPDATE department SET dmano=NULL WHERE dmano=(SELECT eno FROM deleted);
    DELETE FROM account WHERE eno=(SELECT eno FROM deleted);
END

--删除员工的时候，如果他所在的部门只有他一个人，则将其部门删除
CREATE TRIGGER delete_employee_delete_department
ON employee
FOR DELETE
AS
BEGIN
    DELETE FROM department WHERE dno=(SELECT dno FROM deleted) AND (SELECT COUNT(*) FROM employee WHERE dno=(SELECT dno FROM deleted))=0;
END

DELETE FROM employee WHERE eno='00045';

--设置触发器，当建立部门的时候，将其管理员的员工表中的部门编号置为该部门的编号
CREATE TRIGGER insert_department
ON department
FOR INSERT
AS
BEGIN
    UPDATE employee SET dno=(SELECT dno FROM inserted) WHERE eno=(SELECT dmano FROM inserted);
END
INSERT INTO department VALUES('002','人事部','00002','NONE');

--向签到表中插入数据，时间为当前时间，员工编号为%1
INSERT INTO attendance_sheet VALUES('00001','3',GETDATE(),'请假了');

--将attendance_sheet type限制在1，2，3之间
ALTER TABLE attendance_sheet ADD CONSTRAINT typecheck
CHECK (type IN ('1','2','3'));
--输出attendance_sheet的所有信息，其中当type=1，2，3时，分别显示“上班”，“下班”，“请假了”
GO
SELECT CONVERT(date, time) AS 'date', CONVERT(time, time) AS 'time', CASE type WHEN '1' THEN '上班' WHEN '2' THEN '下班' WHEN '3' THEN '请假' END AS 'type', ISNULL(other,'不适用') FROM attendance_sheet WHERE eno='10000'
--按上边写查询在日期在1和2之间的所有信息
SELECT CONVERT(date, time) AS 'date', CONVERT(time, time) AS 'time', CASE type WHEN '1' THEN '上班' WHEN '2' THEN '下班' WHEN '3' THEN '请假' END AS 'type', ISNULL(other,'不适用') FROM attendance_sheet WHERE eno='10000' AND CONVERT(date, time) BETWEEN '2023-12-01' AND '2023-12-31'
INSERT INTO attendance_sheet VALUES('%1','3',GETDATE(),'%2')
--查询特定部门的考勤信息
SELECT e.eno, e.ename, CONVERT(date, a.time) AS 'date', CONVERT(time, a.time) AS 'time', CASE a.type WHEN '1' THEN '上班' WHEN '2' THEN '下班' WHEN '3' THEN '请假' END AS 'type', ISNULL(a.other,'不适用') AS 'other' FROM employee e LEFT JOIN attendance_sheet a ON e.eno = a.eno WHERE e.dno='%1' AND (a.time IS NOT NULL OR a.type IS NOT NULL)

--查找特定部门，账号类别为2的普通员工
SELECT e.eno, e.ename FROM employee e LEFT JOIN department d ON e.dno = d.dno WHERE e.dno = '%1' AND e.eno IN (SELECT eno FROM account WHERE type = '2');
--查找特定员工的考勤信息
SELECT e.eno, e.ename, CONVERT(date, a.time) AS 'date', CONVERT(time(3), a.time) AS 'time', CASE a.type WHEN '1' THEN '上班' WHEN '2' THEN '下班' WHEN '3' THEN '请假' END AS 'type', ISNULL(a.other,'不适用') AS 'other' FROM employee e LEFT JOIN attendance_sheet a ON e.eno = a.eno WHERE e.eno='%1' AND (a.time IS NOT NULL OR a.type IS NOT NULL) AND CONVERT(date, a.time) BETWEEN '%2' AND '%3'
--更新考勤信息 type=3,time='%1'，other='%2'
UPDATE attendance_sheet SET type='3',time='%1',other='%2' WHERE eno='%3' 

--删除考勤信息
DELETE FROM attendance_sheet WHERE eno='%1' AND CONVERT(date, time)='%2'
