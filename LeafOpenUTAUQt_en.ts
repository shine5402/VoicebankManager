<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE TS>
<TS version="2.1" language="en" sourcelanguage="zh_CN">
<context>
    <name></name>
    <message>
        <location filename="EngineUtils/moresamplerconfig.cpp" line="218"/>
        <source>输出的 .wav 文件的采样频率</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfig.cpp" line="219"/>
        <source>输出的 .wav 文件的位深</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfig.cpp" line="220"/>
        <source>开启时, 在resampler模式下生成 .wav 文件 （用于与其他wavtool兼容）。此选项将减慢合成。 </source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfig.cpp" line="221"/>
        <source>对每个音符应用自适应增益，使得当音量为100％时，合成波形的峰值达到最大幅度的一半。full: 对浊音和清音均进行增益； voiced: 只增益浊音；off: 不改变音量。</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfig.cpp" line="222"/>
        <source>基于心理声学响度测量，在修改后使可感知响度保持。</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfig.cpp" line="223"/>
        <source>决定Moresampler如何使音符时间变长。auto: 根据源时长和目标时长自动决定是使用拉伸方式还是循环方式。可使用 e 和 Me flag 来覆盖这一行为。</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfig.cpp" line="224"/>
        <source>on: wavtool模式下的合成将多线程运行（将会更快）。full: resampler模式也将在多线程运行。“多线程”意味着将多个线程包装于一个进程中，与同一时间运行多个Moresampler的“多进程”有着本质不同。注意，该特性不被 moresampler-legacy.exe支持。</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfig.cpp" line="225"/>
        <source>检查.wav 文件与对应.llsm 文件和mrq数据项的最后修改时间。如果.wav文件比.llsm要新，则进行重分析。若.wav文件也比mrq数据项要新，则在重分析以生成.llsm文件前进行音高重估计。此特性或许对声库开发者有帮助。 </source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfig.cpp" line="226"/>
        <source>在指定文件路径中输出Debug信息。</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfig.cpp" line="227"/>
        <source>从文件夹名推测音高。例如，如果给定的样本位于一个名为“C_D4”的文件夹下，Moresampler将在接近D4的范围（294 Hz左右）内进行音高分析。</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfig.cpp" line="228"/>
        <source>在接合音高与浊音行为估计期间增大浊音化概率，随后进行浊音音高修正；旨在提高特异度和降低灵敏度；适用于嘈杂/粗糙的语音，但会降低干净/流畅语音的质量。 </source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfig.cpp" line="229"/>
        <source>音高的下界(以Hz为单位)。</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfig.cpp" line="230"/>
        <source>音高的上界(以Hz为单位)。</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfig.cpp" line="231"/>
        <source>strict : 当desc.mrq不可用时，从.frq 文件读取音高数据。on : 使用 .frq 文件的音高数据来修正Moresampler自己对音高的猜测。不管该选项是否开启，结果都会保存至desc.mrq。注意：除非被仔细修正，.frq文件提供的音高数据通常无法足够可靠地使Moresampler运作。</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfig.cpp" line="232"/>
        <source>on : Moresampler将自动修复由噪声失真或低音量（量化误差）引起的分析错误。这些错误可能造成音高变换后的“尖锐”与“粗糙”的声音。然而此特性（理论上）可能导致轻微模糊。</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfig.cpp" line="233"/>
        <source>在从.wav文件分析LLSM时自动降噪。更适用于长录音。</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfig.cpp" line="234"/>
        <source>在分析时自动移除输入中存在的次谐波。对尖亮的声音可能有帮助，但会导致呼吸音的质量降低。</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>AvailableTextCodecDialog</name>
    <message>
        <location filename="TextCodecUtils/availabletextcodecdialog.ui" line="14"/>
        <source>支持的编码</source>
        <translation>Supported encoding</translation>
    </message>
    <message>
        <location filename="TextCodecUtils/availabletextcodecdialog.ui" line="20"/>
        <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;支持的编码：&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
        <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;Supported encodings:&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
        <location filename="TextCodecUtils/availabletextcodecdialog.ui" line="27"/>
        <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;您可以通过在此处键入文本来搜索下面显示的字符编码。&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
        <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;You can search for the character encoding shown below by typing text here.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
        <location filename="TextCodecUtils/availabletextcodecdialog.ui" line="30"/>
        <source>键入以搜索</source>
        <translation>Type to search</translation>
    </message>
    <message>
        <location filename="TextCodecUtils/availabletextcodecdialog.ui" line="43"/>
        <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;此处显示Qt支持的文本编码的列表。您可以通过右键菜单复制它们其中的一个。&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
        <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;Here shows text encodings that Qt support. You can copy one of them by right-click menu. &lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
        <location filename="TextCodecUtils/availabletextcodecdialog.ui" line="59"/>
        <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;在Qt的内部实现中，以上的有些编码是同一种编码的别名。&lt;/p&gt;&lt;p&gt;您可以通过右键菜单来复制相应字符串到剪贴板，或者直接双击或选择后确定以应用至父窗口。&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
        <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;In the internal implementation of Qt, some of the above encodings are aliases of the same encoding.&lt;/p&gt;&lt;p&gt;You can copy the corresponding string to the clipboard via the right-click menu, or double-click or select and click OK to apply to the parent window.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
        <location filename="TextCodecUtils/availabletextcodecdialog.ui" line="79"/>
        <source>复制该编码名称</source>
        <translation>Copy the name of the encoding</translation>
    </message>
    <message>
        <location filename="TextCodecUtils/availabletextcodecdialog.ui" line="82"/>
        <source>将选定的编码名称复制到剪贴板</source>
        <translation>Copy the selected encoding name to the clipboard</translation>
    </message>
</context>
<context>
    <name>EditorWindow</name>
    <message>
        <location filename="editorwindow.ui" line="13"/>
        <source>EditorWindow</source>
        <translation></translation>
    </message>
</context>
<context>
    <name>ImageCropperContainer</name>
    <message>
        <location filename="../ImageCropper/src/imagecroppercontainer.ui" line="14"/>
        <source>Form</source>
        <translation></translation>
    </message>
</context>
<context>
    <name>MonitorFoldersAddDialog</name>
    <message>
        <location filename="VoiceBankUtils/monitorfoldersadddialog.ui" line="14"/>
        <source>添加一个监视文件夹</source>
        <translation>Add a monitor folder</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/monitorfoldersadddialog.ui" line="20"/>
        <source>输入要添加的被监视文件夹路径，或者使用浏览：</source>
        <translation>Enter the path of the monitored folder you want to add, or use &quot;Browse&quot;:</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/monitorfoldersadddialog.ui" line="34"/>
        <source>浏览</source>
        <translation>Browse</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/monitorfoldersadddialog.cpp" line="23"/>
        <source>选择一个文件夹</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>MonitorFoldersSettingDialog</name>
    <message>
        <location filename="VoiceBankUtils/monitorfolderssettingdialog.ui" line="14"/>
        <source>监视文件夹设定</source>
        <translation>Monitor Folders Seetings</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/monitorfolderssettingdialog.ui" line="20"/>
        <source>添加</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/monitorfolderssettingdialog.ui" line="27"/>
        <source>删除</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/monitorfolderssettingdialog.ui" line="50"/>
        <source>监视文件夹列表：</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/monitorfolderssettingdialog.cpp" line="53"/>
        <source>路径不存在</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/monitorfolderssettingdialog.cpp" line="53"/>
        <source>您输入的路径不存在。监视文件夹列表将不做更改。</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/monitorfolderssettingdialog.cpp" line="56"/>
        <source>路径为空</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/monitorfolderssettingdialog.cpp" line="56"/>
        <source>您并没有输入路径。监视文件夹列表将不做更改。</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>MoresamplerConfig</name>
    <message>
        <location filename="EngineUtils/moresamplerconfig.cpp" line="41"/>
        <location filename="EngineUtils/moresamplerconfig.cpp" line="42"/>
        <source>（空行）</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfig.cpp" line="48"/>
        <source>（注释）</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfig.cpp" line="90"/>
        <source>分析配置</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfig.cpp" line="92"/>
        <source>元标记</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfig.cpp" line="94"/>
        <source>杂项</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfig.cpp" line="96"/>
        <source>输出配置</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfig.cpp" line="98"/>
        <source>合成配置</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfig.cpp" line="100"/>
        <location filename="EngineUtils/moresamplerconfig.cpp" line="106"/>
        <source>未知</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfig.cpp" line="102"/>
        <source>注释</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfig.cpp" line="104"/>
        <source>空行</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfig.cpp" line="111"/>
        <source>（元标记）</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfig.cpp" line="112"/>
        <source>元标记提供了一种快捷的方式让您多个flag合并为一个。元标记在全局配置文件中被定义,并通过 M+数字 (例如 M1, M2, M3) 的形式使用。通过在元标记之后放置点和数字，对应的 flag 的有效数值将按照数字缩放（以百分比表示，只要缩放的结果仍然在每个标志的允许范围内）。</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>MoresamplerConfigAddNewDialog</name>
    <message>
        <location filename="EngineUtils/moresamplerconfigaddnewdialog.ui" line="14"/>
        <source>添加一个新的Moresampler配置项</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfigaddnewdialog.ui" line="20"/>
        <source>从下列配置项中选择一个来添加：</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>MoresamplerConfigsAddNewModel</name>
    <message>
        <location filename="EngineUtils/moresamplerconfigsaddnewmodel.cpp" line="6"/>
        <location filename="EngineUtils/moresamplerconfigsaddnewmodel.cpp" line="70"/>
        <source>（空行）</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfigsaddnewmodel.cpp" line="6"/>
        <location filename="EngineUtils/moresamplerconfigsaddnewmodel.cpp" line="70"/>
        <source>（注释）</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfigsaddnewmodel.cpp" line="8"/>
        <location filename="EngineUtils/moresamplerconfigsaddnewmodel.cpp" line="72"/>
        <source>（元标记）</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfigsaddnewmodel.cpp" line="29"/>
        <source>设置项</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfigsaddnewmodel.cpp" line="31"/>
        <source>类型</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfigsaddnewmodel.cpp" line="33"/>
        <source>说明</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfigsaddnewmodel.cpp" line="73"/>
        <source>元标记</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>MoresamplerConfigsDelegate</name>
    <message>
        <location filename="EngineUtils/moresamplerconfigsdelegate.cpp" line="24"/>
        <location filename="EngineUtils/moresamplerconfigsdelegate.cpp" line="25"/>
        <source>是</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfigsdelegate.cpp" line="24"/>
        <location filename="EngineUtils/moresamplerconfigsdelegate.cpp" line="25"/>
        <source>否</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>MoresamplerConfigsDialog</name>
    <message>
        <location filename="EngineUtils/moresamplerconfigsdialog.ui" line="20"/>
        <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;您可以通过该按钮来删除当前选中的行。&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfigsdialog.ui" line="23"/>
        <source>删除</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfigsdialog.ui" line="53"/>
        <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;您可以通过该按钮在文件的最后一行新建一个配置项。&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfigsdialog.ui" line="56"/>
        <source>添加</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfigsdialog.ui" line="63"/>
        <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;这里显示配置文件中的配置项。&lt;/p&gt;&lt;p&gt;您可以双击“值”一列来编辑配置项的值。如果您编辑的是全局配置，您可以双击“是否覆盖声库配置”来选择是否覆盖各个声库中定义的配置。&lt;/p&gt;&lt;p&gt;若要添加和删除配置项，使用左下角的“添加”和“删除”按钮。&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfigsdialog.cpp" line="18"/>
        <source>编辑“%1”的Moresampler配置</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfigsdialog.cpp" line="20"/>
        <source>编辑名称位置的音源的Moresampler配置</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfigsdialog.cpp" line="23"/>
        <source>编辑全局Moresampler配置</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfigsdialog.cpp" line="24"/>
        <source>当前正在编辑：%1</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfigsdialog.cpp" line="41"/>
        <source>没有可删除的项</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfigsdialog.cpp" line="41"/>
        <source>当前配置文件的配置项目数为0，所以无法删除项目。</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfigsdialog.cpp" line="51"/>
        <source>（空行）</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfigsdialog.cpp" line="53"/>
        <source>（注释）</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfigsdialog.cpp" line="55"/>
        <source>（元标记）</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfigsdialog.cpp" line="58"/>
        <source>指定元标记的序数</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfigsdialog.cpp" line="58"/>
        <source>在下面的输入框中输入一个数字。该数字将作为调用元标记时应当使用的系数。比如，您想要使用M1，就在下框中输入1.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfigsdialog.cpp" line="78"/>
        <source>您设置的值“%1”无法应用于第%2行。请修改后重试。
</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfigsdialog.cpp" line="81"/>
        <location filename="EngineUtils/moresamplerconfigsdialog.cpp" line="90"/>
        <source>设置的值无效</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfigsdialog.cpp" line="90"/>
        <source>您设置的值“%1”无法应用于第%2行。请修改后重试。</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>MoresamplerConfigsModel</name>
    <message>
        <location filename="EngineUtils/moresamplerconfigsmodel.cpp" line="16"/>
        <location filename="EngineUtils/moresamplerconfigsmodel.cpp" line="32"/>
        <source>设置项</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfigsmodel.cpp" line="18"/>
        <location filename="EngineUtils/moresamplerconfigsmodel.cpp" line="34"/>
        <source>值</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfigsmodel.cpp" line="20"/>
        <location filename="EngineUtils/moresamplerconfigsmodel.cpp" line="36"/>
        <source>分类</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfigsmodel.cpp" line="22"/>
        <source>是否覆盖声库配置</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfigsmodel.cpp" line="24"/>
        <location filename="EngineUtils/moresamplerconfigsmodel.cpp" line="38"/>
        <source>说明</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfigsmodel.cpp" line="91"/>
        <location filename="EngineUtils/moresamplerconfigsmodel.cpp" line="141"/>
        <source>是</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfigsmodel.cpp" line="91"/>
        <source>否</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfigsmodel.cpp" line="93"/>
        <source>（不支持）</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>TextCodecConvertDialog</name>
    <message>
        <location filename="TextCodecUtils/textcodecconvertdialog.ui" line="14"/>
        <source>转换文本编码</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="TextCodecUtils/textcodecconvertdialog.ui" line="20"/>
        <location filename="TextCodecUtils/textcodecconvertdialog.ui" line="61"/>
        <source>支持的编码</source>
        <translation type="unfinished">Supported encoding</translation>
    </message>
    <message>
        <location filename="TextCodecUtils/textcodecconvertdialog.ui" line="31"/>
        <location filename="TextCodecUtils/textcodecconvertdialog.ui" line="95"/>
        <source>Shift-JIS</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="TextCodecUtils/textcodecconvertdialog.ui" line="36"/>
        <location filename="TextCodecUtils/textcodecconvertdialog.ui" line="100"/>
        <source>GB18030</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="TextCodecUtils/textcodecconvertdialog.ui" line="41"/>
        <location filename="TextCodecUtils/textcodecconvertdialog.ui" line="105"/>
        <source>Big5</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="TextCodecUtils/textcodecconvertdialog.ui" line="46"/>
        <location filename="TextCodecUtils/textcodecconvertdialog.ui" line="110"/>
        <source>UTF-8</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="TextCodecUtils/textcodecconvertdialog.ui" line="54"/>
        <source>转换后文本预览：</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="TextCodecUtils/textcodecconvertdialog.ui" line="81"/>
        <source>转换前文本：</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="TextCodecUtils/textcodecconvertdialog.ui" line="118"/>
        <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;打开此项后，程序将在预览窗口中同时输出系统编码下对您选择编码字符串的重解码后的显示效果。对文件名转换来说，此项十分有帮助。&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="TextCodecUtils/textcodecconvertdialog.ui" line="121"/>
        <source>在预览中输出在系统编码下重解码的预览</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="TextCodecUtils/textcodecconvertdialog.cpp" line="97"/>
        <source>&lt;h4&gt;以%1进行解码的预览：&lt;/h4&gt;&lt;pre&gt;%2&lt;/pre&gt;&lt;h4&gt;使用系统编码重解码后的预览&lt;/h4&gt;&lt;pre&gt;%3&lt;/pre&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="TextCodecUtils/textcodecconvertdialog.cpp" line="129"/>
        <source>对%1进行编码转换</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>TextCodecSettingDialog</name>
    <message>
        <location filename="VoiceBankUtils/textcodecsettingdialog.ui" line="14"/>
        <source>文本编码设定</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/textcodecsettingdialog.ui" line="25"/>
        <source>readme.txt的字符编码</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/textcodecsettingdialog.ui" line="36"/>
        <location filename="VoiceBankUtils/textcodecsettingdialog.ui" line="77"/>
        <source>Shift-JIS</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/textcodecsettingdialog.ui" line="41"/>
        <location filename="VoiceBankUtils/textcodecsettingdialog.ui" line="82"/>
        <source>GB18030</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/textcodecsettingdialog.ui" line="46"/>
        <location filename="VoiceBankUtils/textcodecsettingdialog.ui" line="87"/>
        <source>Big5</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/textcodecsettingdialog.ui" line="51"/>
        <location filename="VoiceBankUtils/textcodecsettingdialog.ui" line="92"/>
        <source>UTF-8</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/textcodecsettingdialog.ui" line="59"/>
        <source>跟随默认编码？</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/textcodecsettingdialog.ui" line="66"/>
        <source>character.txt的字符编码</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/textcodecsettingdialog.ui" line="103"/>
        <location filename="VoiceBankUtils/textcodecsettingdialog.ui" line="110"/>
        <source>支持的编码</source>
        <translation type="unfinished">Supported encoding</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/textcodecsettingdialog.ui" line="119"/>
        <source>要设置文本编码的音源：</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/textcodecsettingdialog.ui" line="126"/>
        <location filename="VoiceBankUtils/textcodecsettingdialog.cpp" line="61"/>
        <source>（默认编码）</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/textcodecsettingdialog.ui" line="133"/>
        <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;注意：如果您要手动指定编码的话，请注意输入QTextCodec的codecForName()函数支持的编码对应字符串。&lt;/p&gt;&lt;p&gt;您可以使用文本框旁的按钮来查看QTextCodec支持的编码及其别名，双击或选择后确定可以直接应用至本对话框。&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/textcodecsettingdialog.cpp" line="49"/>
        <source>设定%1的读取用文本编码</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>VoiceBank</name>
    <message>
        <location filename="VoiceBankUtils/voicebank.cpp" line="635"/>
        <source>&lt;p style=&quot;color:red&quot;&gt;错误：没有为此音源库找到character.txt。在音源使用过程中将无法查看音源名称、图像等信息。&lt;/p&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebank.cpp" line="649"/>
        <source>&lt;p style=&quot;color:red&quot;&gt;错误：character.txt中的name字段没有被设定。在音源使用过程中音源区域将显示文件夹名称。&lt;/p&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebank.cpp" line="663"/>
        <source>&lt;p style=&quot;color:red&quot;&gt;错误：character.txt中的image字段没有被设定。在音源使用过程中音源区域将不显示图片。&lt;/p&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebank.cpp" line="677"/>
        <source>(&lt;p style=&quot;color:red&quot;&gt;错误：找不到character.txt中设定的图片文件（%1）。在音源使用过程中将音源区域将不显示图片。&lt;/p&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebank.cpp" line="692"/>
        <source>&lt;p style=&quot;color:red&quot;&gt;错误：character.txt中设定的图片文件没有正常读取。是不是图片格式与后缀名不符？亦或是文件损坏？&lt;/p&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebank.cpp" line="694"/>
        <source>&lt;p style=&quot;color:red&quot;&gt;错误：character.txt中设定的图片文件（%1*%2）不符合UTAU的图标要求（比例1:1）。在音源使用过程中将音源区域图片可能显示不正确，或者无法显示。&lt;/p&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebank.cpp" line="708"/>
        <source>&lt;p style=&quot;color:red&quot;&gt;错误：找不到readme.txt。音源的README将无法显示。&lt;/p&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebank.cpp" line="722"/>
        <source>&lt;p style=&quot;color:red&quot;&gt;错误：在读取音源图片时发生了一个异常。或许重载此音源能解决这个问题。&lt;/p&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebank.cpp" line="736"/>
        <source>&lt;p style=&quot;color:red&quot;&gt;错误：无法打开readme.txt。或许被其他程序占用了？或者是文件系统问题？日志可以提供更多信息。&lt;/p&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebank.cpp" line="750"/>
        <source>&lt;p style=&quot;color:red&quot;&gt;错误：无法打开character.txt。或许被其他程序占用了？或者是文件系统问题？日志可以提供更多信息。&lt;/p&gt;</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>VoiceBankIconCropDialog</name>
    <message>
        <location filename="VoiceBankUtils/voicebankiconcropdialog.ui" line="23"/>
        <source>键入目标文件名，文件格式将根据后缀自动推断。透明度将会在白色背景上绘制后再保存。默认为“icon.jpg”</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankiconcropdialog.ui" line="30"/>
        <source>目标文件名：</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankiconcropdialog.ui" line="47"/>
        <source>在选择好作为图标的范围之后，按下确定以应用</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankiconcropdialog.cpp" line="11"/>
        <source>为音源库“%1”设定新图标</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>VoiceBankManagerWindow</name>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="14"/>
        <source>音源管理器</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="21"/>
        <source>音源库列表：</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="56"/>
        <source>共 个</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="66"/>
        <source>键入以搜索</source>
        <translation>Type to search</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="86"/>
        <source>文件</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="94"/>
        <source>选项</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="102"/>
        <source>帮助</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="109"/>
        <source>工具</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="113"/>
        <source>（独立）编码转换器</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="217"/>
        <source>播放样例</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="259"/>
        <source>音源库名称</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="290"/>
        <source>导入音源库...</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="293"/>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="296"/>
        <source>导入一个外部音源库用于管理</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="301"/>
        <source>重载</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="304"/>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="307"/>
        <source>重新载入监视文件夹下的音源库</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="312"/>
        <source>对选定的音源库进行原音设定（oto.ini）...</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="315"/>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="318"/>
        <source>在原音设定编辑器中编辑该音源库的oto.ini</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="323"/>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="326"/>
        <source>退出</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="331"/>
        <source>监视文件夹...</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="334"/>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="337"/>
        <source>修改程序寻找音源的位置</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="342"/>
        <source>默认文本编码...</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="345"/>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="348"/>
        <source>修改程序读取音源文件时默认使用的编码</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="353"/>
        <source>关于</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="356"/>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="359"/>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="556"/>
        <source>关于本程序</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="364"/>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="571"/>
        <source>关于 Qt</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="367"/>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="370"/>
        <source>关于本程序使用的 Qt 框架</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="375"/>
        <source>设置读取用线程池的最大大小...</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="378"/>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="381"/>
        <source>（高级）改变程序读取音源库时的最大线程数。请确保您在知道自己在做什么之后再更改此项设置。</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="386"/>
        <source>编辑全局Moresampler设置</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="389"/>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="392"/>
        <source>在编辑器中打开一个moreconfig.txt并以全局模式编辑</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="397"/>
        <source>随机选择一个音源</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="400"/>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="403"/>
        <source>在音源列表中随机选择一个音源。在拿不定主意的时候说不定会有帮助。</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="408"/>
        <source>转换文本文件...</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="411"/>
        <source>在文件编码转换器中打开一个文本文件</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="416"/>
        <source>转换文件名...</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="419"/>
        <source>在文件编码转换器中打开一个文件夹以转换文件名</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="36"/>
        <source>加载中</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="110"/>
        <source>共 %1 个</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="113"/>
        <source>没有音源。</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="124"/>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="126"/>
        <source>音源“%1”读取完毕</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="145"/>
        <source>打开...</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="147"/>
        <source>打开音源文件夹</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="149"/>
        <source>在资源管理器中打开该音源的文件夹。</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="152"/>
        <source>打开character.txt</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="154"/>
        <source>在系统关联的文本编辑器中打开该音源的character.txt。</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="157"/>
        <source>打开readme.txt</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="159"/>
        <source>在系统关联的文本编辑器中打开该音源的readme.txt。</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="164"/>
        <source>复制...路径</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="166"/>
        <source>复制音源路径</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="168"/>
        <source>复制该音源的文件夹路径到剪贴板。</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="171"/>
        <source>复制character.txt的文件路径</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="173"/>
        <source>复制该音源的character.txt的路径到剪贴板。</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="176"/>
        <source>复制readme.txt的文件路径</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="178"/>
        <source>复制该音源的readme.txt路径到剪贴板。</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="183"/>
        <source>修改...</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="185"/>
        <source>修改音源的名称...</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="187"/>
        <source>为该音源指定一个新名称。</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="190"/>
        <source>修改音源的图标...</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="192"/>
        <source>为该音源指定一个新图标。</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="198"/>
        <source>编码相关</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="200"/>
        <source>为该音源单独设置文本编码...</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="202"/>
        <source>为该音源设置读取用文本编码。注意，这仅在本软件中有效。</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="207"/>
        <source>对character.txt进行编码转换...</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="209"/>
        <source>在文件编码转换器中转换该音源character.txt的编码。</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="212"/>
        <source>对readme.txt进行编码转换...</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="214"/>
        <source>在文件编码转换器中转换该音源readme.txt的编码。</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="217"/>
        <source>对WAV文件名进行编码转换...</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="219"/>
        <source>在文件编码转换器中转换该音源的WAV文件名的编码。</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="224"/>
        <source>引擎相关</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="226"/>
        <source>编辑该音源的Moresampler声库配置...</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="228"/>
        <source>编辑该声库的Moresampler声库配置。只有在您使用Moresampler时起效。</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="233"/>
        <source>重载此音源</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="235"/>
        <source>重新从硬盘加载此音源。</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="272"/>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="292"/>
        <source>打开失败</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="272"/>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="292"/>
        <source>无法打开%1。</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="314"/>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="332"/>
        <source>剪贴板仍会被更改</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="314"/>
        <source>即使您没有要求程序创建character.txt，程序也将把路径复制到剪贴板。但还是请您注意，这个路径并没有指向有效的文件。</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="332"/>
        <source>即使您没有要求程序创建readme.txt，程序也将把路径复制到剪贴板。但还是请您注意，这个路径并没有指向有效的文件。</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="357"/>
        <source>character.txt不存在</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="357"/>
        <source>您选定的音源不存在character.txt。所以无法进行转换操作。</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="376"/>
        <source>readme.txt不存在</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="376"/>
        <source>您选定的音源不存在readme.txt。所以无法进行转换操作。</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="394"/>
        <source>%1的WAV文件名</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="415"/>
        <source>%1（%2）</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="424"/>
        <source>转换中出了些问题</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="424"/>
        <source>&lt;h3&gt;程序在转换以下文件时出了些错误&lt;/h3&gt;&lt;pre&gt;%1&lt;/pre&gt;&lt;p&gt;这些文件应当都保持在原有的状态。您可以排查问题后重试。&lt;/p&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="430"/>
        <source>转换成功完成</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="430"/>
        <source>音源%1的WAV文件名均已从%2转换至%3。</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="441"/>
        <source>文件不存在</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="441"/>
        <source>文件%1不存在</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="450"/>
        <source>即将执行编码转换</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="450"/>
        <source>&lt;h3&gt;程序即将对%1执行编码转换（%2 -&gt; %3）&lt;/h3&gt;&lt;p&gt;在您单击确定后，程序将会把转换后的结果保存至%1。&lt;/p&gt;&lt;p&gt;但是，程序有必要提醒您编码转换的&lt;b&gt;风险&lt;/b&gt;：由于源编码和目标编码间的可能的映射不对等关系，这种转换可能&lt;b&gt;不可逆&lt;/b&gt;，并且可能使您&lt;b&gt;丢失数据&lt;/b&gt;！&lt;/p&gt;&lt;p&gt;出于安全考虑，程序将保存一份源文件的备份副本（%1.bak），以便出现问题时您可以手动恢复。&lt;/p&gt;&lt;p&gt;确定要执行转换吗？&lt;/p&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="459"/>
        <source>转换失败</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="459"/>
        <source>&lt;h3&gt;程序无法对%1进行写入&lt;/h3&gt;&lt;p&gt;在写入时出现错误。Qt提供的错误描述为%2。&lt;/p&gt;&lt;p&gt;文件应该没有被修改。&lt;/p&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="463"/>
        <source>转换成功</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="463"/>
        <source>&lt;h3&gt;文件编码转换完成&lt;/h3&gt;&lt;p&gt;程序将自动修改该文件的读取用文本编码，之后将实施重载。&lt;/p&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="471"/>
        <source>无法备份%1</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="471"/>
        <source>&lt;h3&gt;程序无法对%1进行备份&lt;/h3&gt;&lt;p&gt;在备份时出现错误。Qt提供的错误说明为：%2&lt;/p&gt;&lt;p&gt;你仍可以令程序继续转换，但是之前提到的&lt;b&gt;风险&lt;/b&gt;仍然存在，且出现问题时您无法恢复。&lt;/p&gt;&lt;p&gt;确定要继续转换吗？&lt;/p&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="556"/>
        <source>&lt;h3&gt;音源管理器&lt;/h3&gt;&lt;p&gt;版本：%1 作者：shine_5402&lt;/p&gt;&lt;p&gt;本程序以 Apache License Version 2.0 分发。&lt;/p&gt;&lt;p&gt;“音源管理器”是为UTAU程序所用音源设计的本地信息管理器。&lt;/p&gt;&lt;p&gt;本程序是 &lt;a href=&quot;https://github.com/shine5402/LeafOpenUTAUQt&quot;&gt;Leaf OpenUTAU Qt Project&lt;/a&gt; 的一部分&lt;/p&gt;&lt;p&gt;UTAU是一款由饴屋/菖蒲（あめや・あやめ）氏开发的免费的歌声合成软件。&lt;/p&gt;&lt;p&gt;本程序使用了以下开源项目：&lt;/p&gt;&lt;ul&gt;&lt;li&gt;LeafPublicQtClasses by shine_5402 (Apache License Version 2.0)&lt;/li&gt;&lt;li&gt;ImageCropper by dimkanovikov and shine_5402 (GNU LGPL v3)&lt;/li&gt;&lt;/ul&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="577"/>
        <source>设定线程池的最大大小</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="577"/>
        <source>（高级）该设置改变程序读取音源库时的最大线程数。请确保您在知道自己在做什么之后再更改此项设置。</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="580"/>
        <source>线程池大小已经被设置为%1</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="612"/>
        <source>选择一个子文件夹</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="612"/>
        <source>您选择的音源有子文件夹。Moresampler的配置文件只对一个同文件夹内的wav文件起效。请选择一个子文件夹来编辑配置：</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="636"/>
        <source>检测到可能的全局配置</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="636"/>
        <source>在监视文件夹的父文件夹中发现了以下可能的Moresampler配置文件。您可以选择其中的一个打开，或者取消来进行浏览。</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="644"/>
        <source>打开一个Moresampler全局配置文件</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="644"/>
        <source>Moresampler 配置文件 (moreconfig.txt)</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="656"/>
        <source>为音源指定一个新名称</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="656"/>
        <source>为路径为%1的音源指定一个新名称（程序会自动转换编码）：</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="660"/>
        <source>已将路径为%1的音源的名称设置为%2。</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="663"/>
        <source>文件无法被打开</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="663"/>
        <source>有一个文件无法被打开。Qt提供的错误字符串为%1</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="667"/>
        <source>路径为%1的音源的character.txt不存在。程序已经自动创建并将名称设置为%1。</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="684"/>
        <source>图像文件 (%1)</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="685"/>
        <source>选择要设定为图标的新图片</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="702"/>
        <source>没有音源</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="702"/>
        <source>没有音源，无法随机选择音源。</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="717"/>
        <source>备份了%1原先的图标，因为目标文件名已存在。</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="722"/>
        <source>无法备份</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="722"/>
        <source>因为重名，程序尝试备份%1原先的图标，但是遇到错误无法完成，操作终止。</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="739"/>
        <source>没有可供播放的样例</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="739"/>
        <source>程序无法找到可供播放的样例文件。</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="767"/>
        <source>正在播放%1的声音样例</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>VoiceBankReadmeInformationDialog</name>
    <message>
        <location filename="VoiceBankUtils/voicebankreadmeinformationdialog.ui" line="14"/>
        <source>音源库信息</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankreadmeinformationdialog.ui" line="54"/>
        <source>播放样例</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankreadmeinformationdialog.ui" line="80"/>
        <source>音源库名称</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>VoiceBankTableModel</name>
    <message>
        <location filename="VoiceBankUtils/voicebanktablemodel.cpp" line="83"/>
        <source>音源名称</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebanktablemodel.cpp" line="85"/>
        <source>音源路径</source>
        <translation type="unfinished"></translation>
    </message>
</context>
</TS>
