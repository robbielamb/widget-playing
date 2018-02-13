include WidgetPlaying.Bootstrap;

let code: string =
  [%bs.raw {|require('Examples/BreadcrumbExample.re')|}] |> Examples.prepCode;

let se = ReasonReact.stringToElement;

let component = ReasonReact.statelessComponent("BreadcrumbExample");

let make = _children => {
  ...component,
  render: _self =>
    <Examples.Example title="Breadcrumbs">
      <BreadCrumb>
        <BreadCrumb.Item> (se("home")) </BreadCrumb.Item>
      </BreadCrumb>
      <BreadCrumb>
        <BreadCrumb.Item> (se("home")) </BreadCrumb.Item>
        <BreadCrumb.Item active=true>
          (se("more"))
        </BreadCrumb.Item>
      </BreadCrumb>
      (Examples.exampleHighlight(code))
    </Examples.Example>
};