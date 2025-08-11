<%@ page import="java.sql.*" %>
<html>
<head>
    <title>Subject List</title>
    <link rel="stylesheet" href="style.css">
</head>
<body>

<div class="menu">
    <a href="index.html">Home</a>
    <a href="subjectlist.jsp">Subject List</a>
    <a href="review.html">Review</a>
</div>

<div class="content">
    <h1>Subject List</h1>
    <table border="1" cellpadding="5" cellspacing="0">
        <tr>
            <th>Topic</th>
            <th>Block Number</th>
            <th>Author Name</th>
        </tr>
        <%
            try {
                Class.forName("com.mysql.cj.jdbc.Driver");
                Connection con = DriverManager.getConnection(
                    "jdbc:mysql://localhost:3306/subject_details", "root", "password"
                );
                Statement st = con.createStatement();
                ResultSet rs = st.executeQuery("SELECT * FROM course_author");

                while (rs.next()) {
                    out.println("<tr><td>" + rs.getString("Topic") + "</td>");
                    out.println("<td>" + rs.getString("Block_number") + "</td>");
                    out.println("<td>" + rs.getString("Author_name") + "</td></tr>");
                }
                con.close();
            } catch (Exception e) {
                out.println("<tr><td colspan='3'>Error: " + e.getMessage() + "</td></tr>");
            }
        %>
    </table>
</div>

</body>
</html>
