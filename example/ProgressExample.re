include WidgetPlaying.Bootstrap;

let code: string =
  [%bs.raw {|require('Examples/ProgressExample.re')|}] |> Examples.prepCode;

let se = ReasonReact.stringToElement;

let component = ReasonReact.statelessComponent("ProgressExample");
let make = (_children) => {
  ...component,
  render: (_self) =>
    <Examples.Example title="Progress Bars">
      <div className="text-center"> (se("0%")) </div>
      <Progress />
      <div className="text-center"> (se("25%")) </div>
      <Progress value=25.0 />
      <div className="text-center"> (se("50%")) </div>
      <Progress value=50.0 />
      <div className="text-center"> (se("100%")) </div>
      <Progress value=100.0 />
      <div className="text-center"> (se("73 of 108")) </div>
      <Progress value=73.0 max=108.0> (se("70/108")) </Progress>
      <div className="text-center"> (se("Multiple bars")) </div>
      <Progress multi=true>
        <Progress bar=true value=15.0> (se("15%")) </Progress>
        <Progress bar=true value=15.0 color=Colors.Background.Success />
        <Progress bar=true value=15.0 color=Colors.Background.Info />
        <Progress bar=true value=15.0 color=Colors.Background.Warning />
        <Progress bar=true value=15.0 color=Colors.Background.Danger />
      </Progress>
      <div className="text-center"> (se("Striped")) </div>
      <Progress value=50.0 color=Colors.Background.Info striped=true>
        (se("Striped"))
      </Progress>
      <div className="text-center"> (se("Animated")) </div>
      <Progress value=50.0 color=Colors.Background.Danger animated=true>
        (se("Animated"))
      </Progress>
      (Examples.highlight(code))
    </Examples.Example>
};