include WidgetPlaying.Bootstrap;

let code: string =
  [%bs.raw {|require('Examples/ProgressExample.re').default|}]
  |> Examples.prepCode;

let se = React.string;

[@react.component]
let make = () =>
  <Examples.Example title="Progress Bars">
    <div className="text-center"> {se("0%")} </div>
    <Progress />
    <div className="text-center"> {se("25%")} </div>
    <Progress value=25.0 />
    <div className="text-center"> {se("50%")} </div>
    <Progress value=50.0 />
    <div className="text-center"> {se("75%")} </div>
    <Progress value=75.0 />
    <div className="text-center"> {se("100%")} </div>
    <Progress value=100.0 />
    <div className="text-center"> {se("73 of 108")} </div>
    <Progress value=73.0 max=108.0> {se("73/108")} </Progress>
    <div className="text-center"> {se("Multiple bars")} </div>
    <Progress multi=true>
      <Progress key="1" bar=true value=15.0> {se("15%")} </Progress>
      <Progress key="2" bar=true value=15.0 color=Colors.Background.Success />
      <Progress key="3" bar=true value=15.0 color=Colors.Background.Info />
      <Progress key="4" bar=true value=15.0 color=Colors.Background.Warning />
      <Progress key="5" bar=true value=15.0 color=Colors.Background.Danger />
    </Progress>
    <div className="text-center"> {se("Striped")} </div>
    <Progress value=50.0 color=Colors.Background.Info striped=true>
      {se("Striped")}
    </Progress>
    <div className="text-center"> {se("Animated")} </div>
    <Progress value=50.0 color=Colors.Background.Danger animated=true>
      {se("Animated")}
    </Progress>
    {Examples.highlight(code)}
  </Examples.Example>;