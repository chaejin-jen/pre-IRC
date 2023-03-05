## Code Convection

### naming
<details>
<summary style="font-Weight : bold; font-size : 12px; color : #CCCCCC;" > 종류 </summary>
<div>

- camel case (eg. dailyUserTable)
- pascal case (eg. DailyUserTable)
	- 네임스페이스, 이벤트, 프로퍼티, 클레스 네임을 지정할 때 주로 사용
	- 클래스 등에서 많이 사용
	- java, C# 등의 언어들에서 권장

- snake case (eg. daily_user_table)
	- C++에서 권장

- 커스텀 (eg. ST_User_CD)
	- 접두사(두자리)_풀네임(단어)_약어....
	- 접두사 대문자, 단어의 첫글짜 대문자, 약어 대문자

</div>
</details>

- 변수명
- 함수명
- 클래스 / 구조체명
- 멤버변수
	- private
	- public
	- const
- 멤버함수
	- private
	- public
	- const

### 

## TODO
- PW 인증

- $nick, $host, $channel, $text, $level

- 닉네임
	- nick
- 사용자 이름 설정
	- names
- 채널 가입
	- channel
		- /CHANNEL ADD -auto #channelname NetworkName
		- /ADDALLCHANS
	- join

- 메세지 송수신
	- channel
	- private

- operators 와 regular users
	- oper
	- kick
	- kickban

- 해야하나?
	- ping

## 구조..

1. client[fd] = info
	- `map<int, ClientInfo>`
2. channel[name] = info
	- `map<Channel, ClientInfo>`
		- `info` has `fd`
	- `map<Channel, pair<int, ClientInfo> >`
		- `info` and `fd` is pair

```
struct ClientInfo{
	//int fd;
	std::string nick;
	std::string host;
	std::string channel; // channel no? (like fd)
	bool is_oper;		 // single channel or multi channel
	// ban_channel;
	//std::string level;
	//std::string text;
};
```


## irssi

### irssi cmd

```
accept     die         knock    notice    sconnect   unload
action     disconnect  knockout notify    script     unnotify
admin      echo        lastlog  op        scrollback unquery
alias      eval        layout   oper      server     unsilence
away       exec        links    part      servlist   upgrade
ban        flushbuffer list     ping      set        uptime
beep       foreach     load     query     sethost    userhost
bind       format      log      quit      silence    ver
cat        hash        lusers   quote     squery     version
cd         help        map      rawlog    squit      voice
channel    hilight     me       recode    stats      wait
clear      ignore      mircdcc  reconnect statusbar  wall
completion info        mode     redraw    time       wallops
connect    invite      motd     rehash    toggle     who
ctcp       ircnet      msg      reload    topic      whois
cycle      ison        names    resize    trace      whowas
dcc        join        nctcp    restart   ts         window
dehilight  kick        netsplit rmreconns unalias
deop       kickban     network  rmrejoins unban
devoice    kill        nick     save      unignore
```

### irssi message levels
Description:
These are the message levels that are used throughout Irssi;
    they describe what kind of message is displayed.

These are the common levels you can use:

```
ACTIONS         Actions by a nickname.
CLIENTCRAP      Irssi's internal messages.
CLIENTERROR     Irssi's internal error messages.
CLIENTNOTICE    Irssi's internal notices.
CRAP            Can be almost anything.
CTCPS           CTCP messages.
DCC             DCC protocol related messages.
DCCMSGS         DCC chat messages.
INVITES         An invite is received.
JOINS           A nickname joins a channel.
KICKS           A nickname gets kicked from a channel.
MODES           A channel mode is modified.
MSGS            Private messages.
NICKS           A nickname changes to another nickname.
NOTICES         Notices sent from a nickname.
PARTS           A nickname leaves a channel.
PUBLIC          Public messages in a channel.
QUITS           A nickname disconnects from IRC.
SNOTES          Notices sent from a server.
TOPICS          A channel topic is modified.
WALLOPS         A wallop is received.
```

These are the special levels you can use:

```
HILIGHT         The text is highlighted.
NEVER           Never ignores or logs the message.
HIDDEN          Hides the message when window HIDELEVEL includes HIDDEN.
NO_ACT          Doesn't trigger any activity in the statusbar.
NOHILIGHT       The text is not highlighted.
```

When using levels from Irssi scripts,
	you need to prepend the level with 'MSGLEVEL_';
	for example 'CRAP' becomes 'MSGLEVEL_CRAP'.
