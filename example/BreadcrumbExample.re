include WidgetPlaying.Bootstrap;

let code: string =
  [%bs.raw {|require('Examples/BreadcrumbExample.re').default|}] |> Examples.prepCode;

let se = React.string;


[@react.component]
let make = () => {
    <Examples.Example title="Breadcrumbs">
      <BreadCrumb>
        <BreadCrumb.Item> (se("home")) </BreadCrumb.Item>
      </BreadCrumb>
      <BreadCrumb>
        <BreadCrumb.Item> (se("home")) </BreadCrumb.Item>
        <BreadCrumb.Item active=true> (se("more")) </BreadCrumb.Item>
      </BreadCrumb>
      (Examples.exampleHighlight(code))
    </Examples.Example>
};

