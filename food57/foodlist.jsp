<%@ page import="java.sql.*" %>
<html>
<head>
    <title>Food List</title>
    <link rel="stylesheet" href="style.css">
</head>
<body>

<div class="menu">
    <a href="index.html">Home</a>
    <a href="foodlist.jsp">Food List</a>
    <a href="recommend.html">Recommendations</a>
</div>

<div class="content">
    <h1>Food List</h1>
    <table border="1" cellpadding="5" cellspacing="0">
        <tr>
            <th>Food Name</th>
            <th>Chef Name</th>
        </tr>
        <%
            try {
                Class.forName("com.mysql.cj.jdbc.Driver");
                Connection con = DriverManager.getConnection(
                    "jdbc:mysql://localhost:3306/food", "root", "password"
                );
                Statement st = con.createStatement();
                ResultSet rs = st.executeQuery("SELECT * FROM foodlist");

                while (rs.next()) {
                    out.println("<tr><td>" + rs.getString("Foodname") + "</td>");
                    out.println("<td>" + rs.getString("Chef_name") + "</td></tr>");
                }
                con.close();
            } catch (Exception e) {
                out.println("<tr><td colspan='2'>Error: " + e.getMessage() + "</td></tr>");
            }
        %>
    </table>
</div>

</body>
</html>
