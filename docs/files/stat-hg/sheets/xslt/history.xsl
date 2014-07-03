<?xml version="1.0" encoding="us-ascii"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:output method="html" encoding="utf-8" doctype-public="-//W3C//DTD XHTML 1.0 Strict//EN" doctype-system="http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd" omit-xml-declaration="yes"/>

<xsl:template match="report">

 <xsl:variable name="title">
  <xsl:text>Development Statistics for </xsl:text>
  <xsl:value-of select="@project-name"/>
 </xsl:variable>

 <html>
  <head>
   <title><xsl:value-of select="$title"/></title>
   <link rel='stylesheet' type='text/css' href='css/history.css'></link>
  </head>
  <body>
   <h1><xsl:value-of select="$title"/></h1>
   <p class="summary">
    <xsl:text>Date: </xsl:text>
    <xsl:value-of select="@date"/>
   </p>
   <p class="summary">
    <xsl:text>Head revision: </xsl:text>
    <xsl:value-of select="dataset[@id='commit-log']/data[last()]/prop[@name='rev']/@value"/>
   </p>
   <p class="summary">
    <xsl:text>Report period: </xsl:text>
    <xsl:value-of select="substring(dataset[@id='commit-log']/data[1]/prop[@name='date']/@value, 1, 10)"/>
    <xsl:text> to </xsl:text>
    <xsl:value-of select="substring(dataset[@id='commit-log']/data[last()]/prop[@name='date']/@value, 1, 10)"/>
   </p>

   <br/>
   <p class="link"><a href="#tags">Repository tags</a></p>
   <p class="link"><a href="#commit">Commit log</a></p>
   <p class="link"><a href="#activity">Development activity</a></p>
   <p class="link"><a href="#files">File statistics</a></p>
   <p class="link"><a href="#loc-and-churn">LOC and churn</a></p>

   <div id="loc">
    <h3>Lines of code</h3>
    <img src='png\lines-of-code.png'/>
   </div>

   <div id="tags">
    <a name="tags"></a>
    <xsl:apply-templates select="dataset[@id='repository-tags']"/>
   </div>

   <div id="commit">
    <a name="commit"></a>
    <h2>Commit log</h2>
    <br/>
    <p class="link"><a href="#commit-log">Last commits done</a></p>
    <p class="link"><a href="#commit-tag-cloud">Tag cloud of commit messages</a></p>

    <a name="commit-log"></a>
    <h3>Last commits done</h3>
    <xsl:apply-templates select="dataset[@id='commit-log']"/>
    <a name="commit-tag-cloud"></a>
    <h3>Tag cloud of commit messages</h3>
    <p class='tag-cloud'>
     <xsl:apply-templates select="dataset[@id='commit-tag-cloud']"/>
    </p>
   </div>

   <div id="activity">
    <a name="activity"></a>
    <h2>Development activity</h2>

    <br/>
    <p class="link"><a href="#activity-commit">Commit activity</a></p>
    <p class="link"><a href="#activity-author">Author activity</a></p>
    <p class="link"><a href="#activity-hourofday">Activity by hour of day</a></p>
    <p class="link"><a href="#activity-dayofweek">Activity by day of week</a></p>
    <p class="link"><a href="#activity-punchcard">Activity punchcard</a></p>

    <a name="activity-commit"></a>
    <h3>Commit activity</h3>
    <img src='png\activity.png'/>

    <a name="activity-author"></a>
    <h3>Author activity</h3>
    <img src='png\author-activity.png'/>

    <a name="activity-hourofday"></a>
    <h3>Activity by hour of day</h3>
    <img src='png\activity-by-hour-of-day.png'/>

    <a name="activity-dayofweek"></a>
    <h3>Activity by day of week</h3>
    <img src='png\activity-by-day-of-week.png'/>

    <a name="activity-punchcard"></a>
    <h3>Activity punchcard</h3>
    <img src='png\activity-punchcard.png'/>
   </div>

   <div id="files">
    <a name="files"></a>
    <h2>File statistics</h2>
    <h3>File count and average size</h3>
    <img src='png\file-count-and-size.png'/>
   </div>

   <div id="loc-and-churn">
    <h2>LOC and churn</h2>
    <h3>LOC and churn</h3>
    <a name="loc-and-churn"></a>
    <img src='png\loc-and-churn.png'/>
   </div>

   <br/>
  </body>
 </html>
</xsl:template>

<xsl:template match="dataset[@id='repository-tags']">
 <h2>Repository tags</h2>
 <h3>Tagged revisions</h3>
 <table cellpadding="0" cellspacing="0">
  <tr>
   <th>rev</th>
   <th>tag</th>
   <th>lines</th>
   <th>added</th>
   <th>removed</th>
   <th>churn</th>
  </tr>
  <xsl:for-each select="data">
   <xsl:sort select="prop[@name='rev']/@value" data-type="number" order="descending"/>
   <xsl:variable name="ins_lines" select="prop[@name='ins_lines']/@value"/>
   <xsl:variable name="del_lines" select="prop[@name='del_lines']/@value"/>
   <xsl:variable name="prev_ins_lines" select="sum(preceding-sibling::data/prop[@name='ins_lines']/@value)"/>
   <xsl:variable name="prev_del_lines" select="sum(preceding-sibling::data/prop[@name='del_lines']/@value)"/>
   <xsl:variable name="loc" select="$prev_ins_lines + $ins_lines - $prev_del_lines - $del_lines"/>
   <xsl:variable name="churn" select="$ins_lines + $del_lines"/>
   <tr>
    <td class="rev"><xsl:value-of select="prop[@name='rev']/@value"/></td>
    <td class="tag"><xsl:value-of select="prop[@name='tag']/@value"/></td>
    <td class="count"><xsl:value-of select="$loc"/></td>
    <td class="count"><xsl:value-of select="$ins_lines"/></td>
    <td class="count"><xsl:value-of select="$del_lines"/></td>
    <td class="percent">
     <xsl:value-of select="format-number($churn * 100. div $loc, '0.0')"/>
     <xsl:text>%</xsl:text>
    </td>
   </tr>
  </xsl:for-each>
 </table>
</xsl:template>

<xsl:template match="dataset[@id='commit-log']">
 <table cellpadding="0" cellspacing="0">
  <tr>
   <th>rev</th>
   <th>date</th>
   <th>comment</th>
  </tr>
  <xsl:for-each select="data">
   <xsl:sort select="prop[@name='rev']/@value" data-type="number" order="descending"/>
   <xsl:if test="position() &lt;= 20">
    <tr>
     <td class="rev"><xsl:value-of select="prop[@name='rev']/@value"/></td>
     <td class="date"><xsl:value-of select="prop[@name='date']/@value"/></td>
     <td class="message"><xsl:value-of select="prop[@name='desc']/@value"/></td>
    </tr>
   </xsl:if>
  </xsl:for-each>
 </table>
</xsl:template>

<xsl:template match="dataset[@id='commit-tag-cloud']">
 <xsl:variable name="max-score">
  <xsl:for-each select="data/prop[@name='occurrences']/@value">
   <xsl:sort data-type="number" order="descending"/>
   <xsl:if test="position() = 1">
    <xsl:value-of select="."/>
   </xsl:if>
  </xsl:for-each>
 </xsl:variable>
 <xsl:variable name="min-score">
  <xsl:for-each select="data/prop[@name='occurrences']/@value">
   <xsl:sort data-type="number" order="ascending"/>
   <xsl:if test="position() = 1">
    <xsl:value-of select="."/>
   </xsl:if>
  </xsl:for-each>
 </xsl:variable>

 <xsl:for-each select="data">
  <xsl:sort select="prop[@name='term']/@value" order="ascending"/>
  <xsl:variable name="score" select="prop[@name='occurrences']/@value"/>
  <xsl:if test="$score &gt; 10">
   <xsl:element name="span">
    <xsl:attribute name="class">
     <xsl:text>tag</xsl:text>
     <xsl:value-of select="format-number(($score - $min-score) div ($max-score - $min-score) * 4 + 1, '#')"/>
    </xsl:attribute>
    <xsl:value-of select="prop[@name='term']/@value"/>
   </xsl:element>
   <xsl:text> </xsl:text>
  </xsl:if>
 </xsl:for-each>
</xsl:template>

</xsl:stylesheet>
