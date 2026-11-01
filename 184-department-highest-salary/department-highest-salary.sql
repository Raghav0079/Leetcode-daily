/* Write your T-SQL query statement below */
WITH [join] AS (
    SELECT 
        e.[name],
        e.salary,
        d.[name] as department,
        RANK() OVER (PARTITION BY d.[name] ORDER BY salary DESC) AS numero
    FROM Employee e
    INNER JOIN Department d ON d.id=e.departmentId
)
SELECT 
    department AS Department,
    name AS Employee,
    salary AS Salary
FROM [join] WHERE numero=1;