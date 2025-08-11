
A. Compare two strings → return YES / NO
(Client should send two strings separated by a newline \n or by |. This code tries newline first, then |.)

c
Copy
Edit
// Paste this in LOGIC SECTION (TCP server expecting "str1\nstr2")
char *s1 = strtok(buffer, "\n");
char *s2 = strtok(NULL, "\n");
if (!s2) { // fallback if client used '|' as delimiter
    s1 = strtok(buffer, "|");
    s2 = strtok(NULL, "|");
}
if (!s1) s1 = "";
if (!s2) s2 = "";
if (strcmp(s1, s2) == 0) strcpy(result, "YES");
else strcpy(result, "NO");
B. Reverse string
c
Copy
Edit
int n = strlen(buffer);
for (int i = 0; i < n; ++i) result[i] = buffer[n-1-i];
result[n] = '\0';
C. Sum of ASCII values of characters (returns integer as string)
c
Copy
Edit
long sum = 0;
for (int i = 0; buffer[i] != '\0'; ++i) sum += (unsigned char)buffer[i];
sprintf(result, "%ld", sum);
D. Count characters -> return length
c
Copy
Edit
int len = strlen(buffer);
sprintf(result, "%d", len);
E. Count vowels (a,e,i,o,u — both cases)
c
Copy
Edit
int cnt = 0;
for (int i=0; buffer[i]; ++i) {
    char c = tolower((unsigned char)buffer[i]);
    if (c=='a'||c=='e'||c=='i'||c=='o'||c=='u') ++cnt;
}
sprintf(result, "%d", cnt);
F. Check palindrome (reply "1"/"0" or "palindrome found"/"no palindrome found")
c
Copy
Edit
int n = strlen(buffer);
int ok = 1;
for (int i=0; i<n/2; ++i) if (buffer[i] != buffer[n-1-i]) { ok = 0; break; }
if (ok) strcpy(result, "palindrome found"); else strcpy(result, "no palindrome found");
// OR for the other variant: sprintf(result, "%d", ok);
G. Largest of 3 numbers (UDP/TCP) — client sends a b c
c
Copy
Edit
int a,b,c;
if (sscanf(buffer, "%d %d %d", &a, &b, &c) < 3) { strcpy(result,"ERR"); }
else {
    int mx = a;
    if (b>mx) mx=b;
    if (c>mx) mx=c;
    sprintf(result, "%d", mx);
}
H. Client sends two numbers → return multiplication
c
Copy
Edit
int a,b;
if (sscanf(buffer, "%d %d", &a, &b) < 2) strcpy(result,"ERR");
else sprintf(result, "%d", a*b);
I. Extract digits from string (return the concatenated digits)
c
Copy
Edit
int j=0;
for (int i=0; buffer[i]; ++i) if (isdigit((unsigned char)buffer[i])) result[j++]=buffer[i];
if (j==0) strcpy(result, ""); else result[j]='\0';
J. Return ASCII values of each character (space-separated)
c
Copy
Edit
char tmp[32];
result[0] = '\0';
for (int i=0; buffer[i]; ++i) {
    sprintf(tmp, "%d", (unsigned char)buffer[i]);
    strcat(result, tmp);
    if (buffer[i+1]) strcat(result, " ");
}
K. Sort list of numbers (descending) — input: 5 10 2 4 7 3
c
Copy
Edit
int nums[100], cnt=0;
char *tok = strtok(buffer, " ");
while (tok && cnt < 100) { nums[cnt++] = atoi(tok); tok = strtok(NULL, " "); }
if (cnt==0) strcpy(result,"");
else {
    // simple bubble sort descending (safe for small n)
    for (int i=0;i<cnt-1;i++) for (int j=0;j<cnt-1-i;j++) if (nums[j] < nums[j+1]) {
        int t = nums[j]; nums[j]=nums[j+1]; nums[j+1]=t;
    }
    char tmp[32]; result[0]='\0';
    for (int i=0;i<cnt;i++) { sprintf(tmp, "%d", nums[i]); strcat(result, tmp); if (i<cnt-1) strcat(result," "); }
}
L. Lookup rollno → name (if asked, use simple in-memory table)
c
Copy
Edit
// Example static mapping
struct rec { int roll; char name[40]; } table[] = { {101,"Aman"}, {102,"Sita"}, {103,"Rahul"} };
int roll;
if (sscanf(buffer, "%d", &roll) != 1) strcpy(result,"NotFound");
else {
    strcpy(result,"NotFound");
    for (int i=0; i< (int)(sizeof(table)/sizeof(table[0])); ++i) {
        if (table[i].roll == roll) { strcpy(result, table[i].name); break; }
    }
}
2) How to quickly adapt the client when question wants multiple pieces (two strings / 3 numbers)
If the question says client sends two strings, change the client input section (in tcp_client.c) to:

c
Copy
Edit
// Read two strings and send them separated by newline
char s1[BUFFER_SIZE], s2[BUFFER_SIZE];
printf("Enter string 1: "); fgets(s1, sizeof s1, stdin); s1[strcspn(s1,"\n")]=0;
printf("Enter string 2: "); fgets(s2, sizeof s2, stdin); s2[strcspn(s2,"\n")]=0;
char sendbuf[BUFFER_SIZE];
snprintf(sendbuf, sizeof sendbuf, "%s\n%s", s1, s2);
send(sock, sendbuf, strlen(sendbuf), 0);
For UDP client do the same but use sendto().